if 0 {
	Author: Altlock

	Description: Calculation done with command line arguments.
}

# Get correct amount of arguments

if {$argc != 3 && $argc != 4} {
	puts "This script requires exactly 3 or 4 numbers to be put in."
	puts "For example: (tclsh $argv0 160 5 39),"
	puts "the calculation of the example is (160 % 5 + 39 = 39)."
	puts "If you put in 4 numbers, the sum will be multiplied by that number."
} elseif {$argc == 3} { ;#If correct amount, calculate
	puts [expr [lindex $argv 0] % [lindex $argv 1] + [lindex $argv 2]]
} else {
	puts [expr ([lindex $argv 0] % [lindex $argv 1] + [lindex $argv 2]) * [lindex $argv 3]]
}
