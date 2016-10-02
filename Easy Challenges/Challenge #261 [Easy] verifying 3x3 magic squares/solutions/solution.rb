# Author: Lim Yao Jie
# Description: Takes in a NxN square array and checks whether it's a magic square.
# Github: www.github.com/causztic

def magic_row?(arr)
  val = false
  arr.each_slice(@length).to_a.each do |a|
    break if (a.reduce(0, :+) != @magic)
    val = true
  end
  return val
end

def magic_diagonal?(arr)
  d = 0
  @length.times { |b| d += arr[b*@length+b] }
  e = 0
  (1..@length).each{ |b| e += arr[b*@length-b] }
  return d == @magic && e == @magic
end

def magic_column?(arr)
  val = false
  c = 0
  @length.times do |a|
    @length.times { |b| c += arr[a+b*@length] }
    break if c != @magic
    val = true
  end
  return val
end


def magic_square?(arr)
  @length = Math.sqrt(arr.length).to_i
  @magic = (@length * (@length * @length + 1))/2
  magic_column?(arr) && magic_diagonal?(arr) && magic_row?(arr)
end

puts magic_square?([2,7,6,9,5,1,4,3,8])
puts magic_square?([3,5,7,8,1,6,4,9,2])