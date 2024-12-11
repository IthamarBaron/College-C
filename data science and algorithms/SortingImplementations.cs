using System;
class Program
{
    public static void Main()
    {
        int[] originalArray = { 5, 3, 8, 6, 2, 7, 4, 1 };

        Console.Write("\t\t\tOriginal Array:\n\t\t\t");
        printArr(originalArray);

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine("\n--- Demonstrating Insertion Sort O(N^2) ---");
        Console.ResetColor();
        int[] insertionArray = (int[])originalArray.Clone();
        InsertionSort(insertionArray);

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine("\n--- Demonstrating Selection Sort O(N^2) ---");
        Console.ResetColor();
        int[] selectionArray = (int[])originalArray.Clone();
        SelectiononSort(selectionArray);

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine("\n--- Demonstrating Merge Sort O(N*LOG(N)) ---");
        Console.ResetColor();
        int[] mergeArray = (int[])originalArray.Clone();
        int[] sortedMergeArray = MergeSort(mergeArray);
        printArr(sortedMergeArray, "Final Merge Sort Result");

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine("\n--- Demonstrating Quick Sort O(N*LOG(N)) ---");
        Console.ResetColor();
        int[] quickArray = (int[])originalArray.Clone();
        QuickSort(quickArray, 0, quickArray.Length);
        printArr(quickArray, "Final Quick Sort Result");

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine("\n--- Demonstrating Bubble Sort O(N^2) ---");
        Console.ResetColor();
        int[] bubbleArray = (int[])originalArray.Clone();
        BoubleSort(bubbleArray);
    }

    public static void InsertionSort(int[] arr)
    {
        for (int i = 1; i < arr.Length; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (arr[j] < arr[j - 1])
                {
                    Swap(arr, j, j - 1);
                }
            }
            printArr(arr, $"Insertion sort (itr {i})");
        }
    } //O(N^2)

    public static void SelectiononSort(int[] arr)
    {
        int min = int.MaxValue;
        int min_index=0;
        for (int i = 0; i < arr.Length; i++)
        {
            printArr(arr, $"Selection Sort (Itr: {i+1})");
            min = int.MaxValue;
            for (int j = i; j < arr.Length; j++)
            {
                if (min > arr[j])
                {
                    min = arr[j];
                    min_index = j;
                }
            }
            Swap(arr, i, min_index);
        }
    }//O(N^2)

    //RETURNS THE SORTED ARRAY, does not modify the given array!
    public static int[] MergeSort(int[] arr)
    {
        printArr(arr, "MergeSort");
        if (arr.Length == 1)
            return arr;
        int mid = (arr.Length) / 2;
        int[] arrLeft = CreateSubArray(arr, 0, mid);
        int[] arrRight = CreateSubArray(arr, mid, arr.Length);
        arrLeft = MergeSort(arrLeft);
        arrRight = MergeSort(arrRight);
        return Merge(arrLeft, arrRight);
    }//O(N*LOG(N))

    public static int[] CreateSubArray(int[] arr, int low, int high)
    {
        int[] newArry= new int[high-low];
        int j = 0;
        for (int i = low; i < high; i++)
        {
            newArry[j++] = arr[i];
        }
        return newArry;
    }//O(N)

    public static int[] Merge(int[] arr1, int[] arr2)
    {
        int[] merge = new int[arr1.Length + arr2.Length];
        int i = 0;
        int j = 0;
        for (int k = 0; k < merge.Length; k++)
        {
            if (j>=arr2.Length||(i < arr1.Length && arr1[i] <= arr2[j]))
                merge[k] = arr1[i++];
            else if (j < arr2.Length)
                merge[k] = arr2[j++];
        }
        return merge;
    }//O(N)

    public static void QuickSort(int[] arr, int low, int high)
    {

        if (low >= high)
            return;
        Console.Write("QuickSort On:");
        PrintSubArray(arr, low, high);
        int pivotIndex = Partition(arr, low, high);
        QuickSort(arr, low, pivotIndex);
        QuickSort(arr, pivotIndex+1, high);
    }//O(N*LOG(N))

    public static int Partition(int[] arr, int low, int high)
    {
        int i = low;
        int j = high - 1;
        int pivot = arr[low];//assume pivot to be local [0]

        while (i < j)
        {
            while (i < high && arr[i] <= pivot)
                i++;

            while (j > low && arr[j] > pivot)
                j--;

            if (i < j)
                Swap(arr, i, j);
        }
        Swap(arr, low, j);
        return j;
    }//O(N)

    static void BoubleSort(int[] arr)
    {
        for (int i = 0; i < arr.Length; i++)
        {
            for (int j = 0; j < arr.Length-1; j++)
            {
                if (arr[j] > arr[j+1])
                    Swap(arr, j, j + 1);
            }
            printArr(arr, $"Bouble sort (itr{i + 1})");
        }
    }//O(N^2)



    static void Swap(int[] arr, int _index0, int _index1)
    {
        if (_index0 != _index1)
        {
            arr[_index0] ^= arr[_index1];
            arr[_index1] ^= arr[_index0];
            arr[_index0] ^= arr[_index1];
        }
    }//O(1)

    //DEBUGS AND VISUALIZATION
    static void printArr(int[] arr, string _message = "PrintArr")
    {
        Console.Write($"{_message}: ");
        if (IsSorted(arr))
            Console.ForegroundColor = ConsoleColor.Green;
        else
            Console.ForegroundColor = ConsoleColor.Red;

        foreach (var item in arr)
            Console.Write($"[{item}] ");
        Console.WriteLine();
        Console.ResetColor();
    }//O(N)
    static void PrintSubArray(int[] arr, int left, int right)
    {
        Console.Write($"Subaray [{left}-{right}]: ");
        for (int i = left; i < right; i++)
        {
            Console.Write($"[{arr[i]}]");
        }
        Console.WriteLine();
    }//O(N)


    static bool IsSorted(int[] arr)
    {
        for (int i = 0; i < arr.Length - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                return false;
            }
        }
        return true;
    }//O(N)
}
