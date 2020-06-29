int dosum(int array[], int arraysize) {
    int sum;
    // initalize i for the loop 
    int i;
    // set sum = 0 to start 
    sum = 0;
    
    // loop through array, add elements to the sum variable 
    for (i = 0; i < arraysize; i++){
        sum += array[i];
    }


    return sum;
}

int domax(int array[], int arraysize) {
    int max;
    // initalize i for the loop 
    int i;
    // set max equal to 0'th element of our array 
    max = array[0];

    // loop through array, compare first two elements, store higher one in 0'th position, repeat until reaches end of array 
    for (i = 0; i < arraysize; i++){
        // if the max variable is LESS THAN our next element, then store that element in our max, compare with next element 
        if (max < array[i]){
            max = array[i];
        }
    }

    return max;
}
