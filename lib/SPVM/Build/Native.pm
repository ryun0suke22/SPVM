package SPVM::Build::Native;

# SPVM::Build::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
use base 'SPVM::Build::Base';

use Carp 'croak', 'confess';

use SPVM::Build::Util;
use SPVM::Build::SPVMInfo;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'native';
  
  return $self;
}

sub get_sub_names_from_module_file {
  my ($self, $module_file) = @_;
  
  return SPVM::Build::Util::get_native_sub_names_from_module_file($module_file);
}

sub get_subs_from_package_name {
  my ($self, $package_name) = @_;
  
  return SPVM::Build::SPVMInfo::get_native_subs_from_package_name($package_name);;
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  my $sub_name_spvm = "SPVM::$sub_name";

  my $cfunc_name = $sub_name_spvm;
  $cfunc_name =~ s/:/_/g;
  
  return $cfunc_name;
}

sub input_dir_dist {
  my ($self, $package_name) = @_;
  
  my $input_dir = SPVM::Build::Util::create_package_load_path('lib', $package_name);
  my $category = $self->category;
  $input_dir =~ s/\.spvm$/.$category/;
  
  return $input_dir;
}

sub build_shared_lib_dist {
  my ($self, $package_name) = @_;
  
  my $input_dir = $self->input_dir_dist($package_name);
  
  my $package_load_path = SPVM::Build::Util::create_package_load_path('lib', $package_name);
  my $sub_names = $self->get_sub_names_from_module_file($package_load_path);
  
  # Build shared library
  my $tmp_shared_lib_file = $self->build_shared_lib(
    package_name => $package_name,
    input_dir => $input_dir,
    output_dir => './spvm_build',
    build_dir => './spvm_build',
    sub_names => $sub_names,
  );
  
  # Create shared lib blib directory
  my $shared_lib_dir = SPVM::Build::Util::convert_package_name_to_shared_lib_dir('blib/lib', $package_name, $self->category);
  mkpath $shared_lib_dir;
  
  # shared lib blib file
  my $shared_lib_file = SPVM::Build::Util::convert_package_name_to_shared_lib_file('blib/lib', $package_name, $self->category);
  
  # Move shared library file to blib directory
  move($tmp_shared_lib_file, $shared_lib_file)
    or die "Can't move $tmp_shared_lib_file to $shared_lib_file";
}

sub build_shared_lib_runtime {
  my ($self, $package_name) = @_;
  
  my $input_dir = SPVM::Build::SPVMInfo::get_package_load_path($package_name);
  my $category = $self->category;
  $input_dir =~ s/\.spvm$/.$category/;

  # Build directory
  my $build_dir = $SPVM::BUILD_DIR;
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  my $output_dir = "$build_dir/$package_file_name." . $self->category;
  mkpath $output_dir;
  
  my $subs = $self->get_subs_from_package_name($package_name);
  my $sub_names = [map { $_->{name} } @$subs];
  
  my $tmp_shared_lib_file = $self->build_shared_lib(
    package_name => $package_name,
    input_dir => $input_dir,
    output_dir => $output_dir,
    build_dir => $output_dir,
    quiet => 1,
    sub_names => $sub_names
  );
  
  return $tmp_shared_lib_file;
}

1;
