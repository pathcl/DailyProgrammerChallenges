# Author: Lim Yao Jie
# Description: Takes in a NxN square array and checks whether it's a magic square.
# Github: www.github.com/causztic

def magic_row?(arr, length)
  val = false
  arr.each_slice(length).to_a.each do |a|
    break if (a.reduce(0, :+) != 15)
    val = true
  end
  return val
end

def magic_diagonal?(arr, length)
  d = 0
  length.times { |b| d += arr[b*length+b] }
  e = 0
  (1..length).each{ |b| e += arr[b*length-b] }
  return d == 15 && e == 15
end

def magic_column?(arr, length)
  val = false
  c = 0
  length.times do |a|
    length.times { |b| c += arr[a+b*length] }
    break if c != 15
    val = true
  end
  return val
end


def magic_square?(arr)
  length = Math.sqrt(arr.length).to_i
  magic_column?(arr, length) && magic_diagonal?(arr, length) && magic_row?(arr, length)
end

puts magic_square?([2,7,6,9,5,1,4,3,8])
puts magic_square?([3,5,7,8,1,6,4,9,2])