function fibonacci_norfc(n) {
    if(n <= 1)
        return 1;

    return fibonacci_norfc(n-1) + fibonacci_norfc(n-2);
}

function fibonacci_rfc(n) {
    if(n <= 1)
        return 1;

    return rfc_invoke(n-1) + rfc_invoke(n-2);
}