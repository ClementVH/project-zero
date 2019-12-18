#ifndef FILE_BINARY_SEARCH_SEEN
#define FILE_BINARY_SEARCH_SEEN

int getClosest(float, int, float, int index1, int index2);

// Returns element closest to target in arr[]
int findClosest(float arr[], int n, float target)
{
    // Corner cases
    if (target <= arr[0])
        return 0;
    if (target >= arr[n - 1])
        return n - 1;

    // Doing binary search
    int i = 0, j = n, mid = 0;
    while (i < j) {
        mid = (i + j) / 2;

        if (arr[mid] == target)
            return mid;

        /* If target is less than array element,
            then search in left */
        if (target < arr[mid]) {

            // If target is greater than previous
            // to mid, return closest of two
            if (mid > 0 && target > arr[mid - 1])
                return getClosest(arr[mid - 1], arr[mid], target, mid - 1, mid);

            /* Repeat for left half */
            j = mid;
        }

        // If target is greater than mid
        else {
            if (mid < n - 1 && target < arr[mid + 1])
                return getClosest(arr[mid], arr[mid + 1], target, mid, mid + 1);
            // update i
            i = mid + 1;
        }
    }

    // Only single element left after search
    return mid;
}

// Method to compare which one is the more close.
// We find the closest by taking the difference
// between the target and both values. It assumes
// that val2 is greater than val1 and target lies
// between these two.
int getClosest(float val1, int val2, float target, int index1, int index2)
{
    if (target - val1 >= val2 - target)
        return index2;
    else
        return index1;
}

#endif
