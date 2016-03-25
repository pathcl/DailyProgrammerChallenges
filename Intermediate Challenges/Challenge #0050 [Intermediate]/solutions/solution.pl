#!/usr/bin/perl --

use v5.18;
use warnings;
use utf8;
use File::Basename;
use Getopt::Long;

binmode STDOUT, ":utf8";

my $version_string = "1.0";

my $base_dir = $ARGV[1] // '.';

print_directory_tree($base_dir, 2, "");

sub print_directory_tree{
    my ($directory, $depth, $preface) = @_;
    say "  $directory";
    say "$preface  +";

    opendir my $dh, $directory or die "Cannot open $directory: $!";
    my @dirs = sort readdir($dh);
    chdir $directory;
    closedir $dh;
    # For each directory
    for my $dir (@dirs) {
        next unless -d $dir and not $dir =~ /^\./;
        say "$preface  |";
        say "$preface  +--$dir";
        if ( $depth - 1 != 0 ) { # if depth < 0 then as far as can go.
            say "$preface  |";
            print "$preface  +--";
            # if not last sub-directory then should extend preface
            # so that sub-subs are further across
            print_directory_tree($dir, $depth - 1, "$preface  |")
        }
    }
    chdir "..";

}

sub usage{
    say "Usage:";
    say "   $0 [LONG-OPTION]...  [DIRECTORY]";
    say "or $0 [SHORT-OPTION]... [DIRECTORY]";
    say "Displays a tree for each DIRECTORY";
    say "";
    say "   -d, --depth     show tree to a depth of d";
    say "   -h, --help      display this help and exit";
    say "   -v, --version   display version information and exit";

}

sub version{
    say "Tree v$version_string";
}
