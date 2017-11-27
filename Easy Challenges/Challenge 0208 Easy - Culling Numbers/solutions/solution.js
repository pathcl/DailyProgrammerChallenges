//tlseabra @github

function cull(input){
    return input.split(' ').filter((a, i, b) => b.indexOf(a) == i).join(' ');
}
