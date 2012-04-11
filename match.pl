#!/usr/bin/perl
use strict;
use warnings;

sub print_usage
{
    print "Usage: match.pl <filename>\n";
}

# Check that we have exactly one argument (the file name)
if ( $#ARGV != 0 )
{
    print_usage ();
}

my $is_debug=0;
if ( !($0 =~ m/rename/) )
{
    $is_debug=1;
}

my $in_filename=$ARGV[0];
$in_filename =~ m/([a-zA-Z0-9]*)(_{0,})(-{1,})([^_]*)([a-zA-Z0-9]+)\.([a-zA-Z0-9]+)/;

# This is to aid debugging : when run as rename/.rename, do not take debug actions
# described in this if clause 
if ( $is_debug )
{
#   DEBUG code goes here ...
    print "\$1 = " . $1 . "\n";
    print "\$2 = " . $2 . "\n";
    print "\$3 = " . $3 . "\n";
    print "\$4 = " . $4 . "\n";
    print "\$5 = " . $5 . "\n";
    print "\$6 = " . $6 . "\n";
}

if ( $1 && $6)
{
    print "$1.$6";
}
if ( !$1 && $3 && $6)
{
    if ($4)
    {
	if($5)
	{
	    print "$4$5.$6";
	}
	else
	{
	    print "$4.$6";
	}
    }
    else
    {
	if ($5)
	{
	    print "$5.$6";
	}
    }
}
