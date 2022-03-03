#include <QCoreApplication>
#include <QDebug>
#include <time.h>
#include <QFile>
#include <QTextStream>

const int MAX_SIZE = 1000000;
int arr[MAX_SIZE];
///////////////////////////////////////////
void quickSorting(int*, int);
void heapSorting(int*, int);
void heapify(int*, int, int);
///////////////////////////////////////////
int main()
{
    clock_t begin, end;
    int count = 0;
    double sumSeconds = 0;
    double seconds = 0;
    QFile file("D:/QTProjects/task1/results.txt");

    if (!file.exists())
    {
        qDebug() << "Can't open file " << file.fileName();
        return 0;
    }
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.resize(0);
    QTextStream textStream(&file);
    textStream << "Быстрая сортировка\n";
    for (int i = 1; i <= 10; i++)
    {

        for (int j = 0; j < MAX_SIZE; j++)
        {
            arr[j] = rand() % (MAX_SIZE - 1);
        }
        //Замеры производительности
        begin = clock();
        quickSorting(arr, MAX_SIZE);
        end = clock();
        seconds = (double)(end - begin) / CLOCKS_PER_SEC;
        //
        textStream << "Time(" << i << ") = " << seconds << "\n";
        sumSeconds += seconds;
        count++;
    }
    textStream << "SrTime = " << sumSeconds / (double)count << "\n";

    count = 0;
    sumSeconds = 0;
    textStream << "\nСортировка кучей(пирамидальная)\n";
    for (int i = 1; i <= 10; i++)
    {

        for (int j = 0; j < MAX_SIZE; j++)
        {
            arr[j] = rand() % (MAX_SIZE - 1);
        }

        //Замеры производительности
        begin = clock();
        heapSorting(arr, MAX_SIZE);
        end = clock();
        seconds = (double)(end - begin) / CLOCKS_PER_SEC;
        //
        textStream << "TimeHeap(" << i << ") = " << seconds << "\n";
        sumSeconds += seconds;
        count++;
    }
    textStream << "SrTime = " << sumSeconds / (double)count << "\n";

    file.close();
    return 0;
}
/////////////////////////////////////////////
void quickSorting(int *sortArr, int size)
{
    int beginIterator = 0;
    int endIterator = size - 1;
    int centerElement = sortArr[size / 2];
    int tempElement = 0;

    do
    {
        while (sortArr[beginIterator] < centerElement) beginIterator++;
        while (sortArr[endIterator] > centerElement) endIterator--;

        if (beginIterator <= endIterator)
        {
            tempElement = sortArr[beginIterator];
            sortArr[beginIterator] = sortArr[endIterator];
            sortArr[endIterator] = tempElement;
            //qSwap(sortArr[beginIterator], sortArr[endIterator]);
            beginIterator++;
            endIterator--;
        }

    } while (beginIterator <= endIterator);

    if (endIterator > 0) quickSorting(sortArr, endIterator + 1);
    if (size > beginIterator) quickSorting(sortArr + beginIterator, size - beginIterator);
}

void heapSorting(int *sortArr, int size)
{
    int tempElement = 0;
   //строим убывающую кучу
   for (int i = size / 2 - 1; i >= 0; i--)
     heapify(sortArr, size, i);

   // сортируем кучу
   for (int i = size - 1; i >= 0; i--)
   {
    //qSwap(sortArr[0], sortArr[i]);
     tempElement = sortArr[0];
     sortArr[0] = sortArr[i];
     sortArr[i] = tempElement;

     heapify(sortArr, i, 0);
   }
}

void heapify(int *inArr, int size, int large)
{
   // Find largest among root, left child and right child
   int largestElement = large;
   int leftBranch = 2*large + 1;
   int rightBranch = 2*large + 2;
   int tempElement = 0;
   if (leftBranch < size && inArr[leftBranch] > inArr[largestElement])
     largestElement = leftBranch;

   if (rightBranch < size && inArr[rightBranch] > inArr[largestElement])
     largestElement = rightBranch;

   // Swap and continue heapifying if root is not largest
   if (largestElement != large)
   {
       //qSwap(inArr[large], inArr[largestElement]);
     tempElement = inArr[large];
     inArr[large] = inArr[largestElement];
     inArr[largestElement] = tempElement;

     heapify(inArr, size, largestElement);
   }
}

