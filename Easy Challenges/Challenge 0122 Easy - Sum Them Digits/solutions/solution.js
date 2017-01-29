//tlseabra @github
function sumDemDigitz(input){
    if(input.toString().length === 1)
        return input;
    else
        return sumDemDigitz(input.toString().split('').reduce((a, b) => a + parseInt(b), 0));
}
