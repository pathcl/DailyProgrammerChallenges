//tlseabra @github

function bitstringCount(n){
    return n.toString(2).split("").reduce((a,b) => parseInt(a)+parseInt(b));
}
