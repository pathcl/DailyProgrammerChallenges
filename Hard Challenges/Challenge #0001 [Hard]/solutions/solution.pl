#!/usr/bin/perl --

use v5.18;
#use warnings;

my @range = 1..100; # viable numbers to guess
my $high = $#range;
my $low = 0;

say "Please think of a number between 1 and 100 inclusive.";

while($high > $low) {
    my $guess = $range[ ($high + $low) / 2 ];
    say "I guess $guess, is that correct, too high, or too low?";

    my $response = <>;
    chomp $response;

    if ( $response eq "correct" ) {
        say "Yay!";
        last;
    }
    elsif ( $response eq "high" ) {
        say "Bah!";
        $high = ( $high + $low ) / 2;
    }
    elsif ( $response eq "low" ) {
        say "Bah!";
        $low = ( $high + $low ) / 2;
    }
}
