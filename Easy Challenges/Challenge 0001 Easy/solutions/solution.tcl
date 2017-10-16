puts "What's your name? "
set name [gets stdin]
puts "What's your age in years? "
set age [gets stdin]
puts "What's your username? "
set username [gets stdin]
set string "Your name is $name, you are $age years old and your username is $username."
puts $string

#Now put it in a file
set file [open "result.txt" "w"]
puts $file $string
close $file

