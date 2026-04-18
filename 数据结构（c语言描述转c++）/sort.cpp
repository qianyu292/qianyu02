//关于各个排序的分析及实现
#include<vector>
#include<queue>
#include<functional>
//插入排序时间复杂度：n次方，非原地排序
void InsertionSort(std::vector<int>&nums, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int key = nums[i];
		int j = i - 1;
		while (j >= 0 && nums[j] > nums[key])
		{
			nums[j+1] = nums[j];
			j--;
		}
		nums[j + 1] = key;
	}
}
//冒泡排序时间复杂度：n次方，原地排序
void Bubbulesort(std::vector<int>&nums, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if (nums[j] > nums[j + 1])
			{
				std::swap(nums[i], nums[j]);
			}
		}
	}
}
//希尔排序时间复杂度:n的logn次方
void shellsort(std::vector<int>&nums, int n)
{
	for (int increment = n / 2; increment > 0; increment /= 2)
	{
		for (int i = increment; i < n; i++) {  // 修正2：从increment开始
			for (int j = i; j >= increment && nums[j] < nums[j - increment]; j -= increment) {
				std::swap(nums[j], nums[j - increment]);
			}
		}
	}
}
//希尔排序的插入排序方式(在某种增量序列下时间复杂度可以到达n的2分之3次方
void shellsort2(std::vector<int>& arr, int n)
{
	for (int increment = n / 2; increment > 0; increment /= 2)
	{
		for (int i = increment; i < n; ++i)
		{
			int temp = arr[i];
			int j = i;
			while(j >= increment && arr[j] < arr[j - increment])
			{
				arr[j] = arr[j - increment];
				j -= increment;
			}
			arr[j] = temp;
		}
	}
}
//堆排序(由前二叉堆可推出时间复杂度为2nlogn-o（n）
void Heapsort(std::vector<int>& nums, int n)
{
	std::priority_queue<int,std::vector<int>,std::greater<int>>pq;
	for (int i = 0; i < n; ++i)
	{
		pq.push(nums[i]);
	}
	std::vector<int>res(n);
	for (int i = 0; i < n; ++i)
	{
		int cur = pq.top();
		pq.pop();
		res[i] = cur;
	}
	nums = res;
}
//归并排序:递归的将数组往下分，再合并（先排序数组前半部分，再排序数组后半部分）时间复杂度：nlogn
void Merge(std::vector<int>& nums, int lo, int mid, int hi);
void Mergesort(std::vector<int>&nums, int lo, int hi)
{
	if (lo >= hi)
	{
		return;
	}
	int mid = lo + (hi - lo) / 2;
	Mergesort(nums, lo, mid);
	Mergesort(nums, mid + 1, hi);
	Merge(nums, lo, mid, hi);
}
void Merge(std::vector<int>& nums, int lo, int mid, int hi)
{
	std::vector<int>temp;
	temp = nums;
	int i = lo, j = mid + 1;
	for (int p = lo; p < hi; ++p)
	{
		if (i >= mid)
		{
			nums[p] = temp[j++];
		}
		else if (j >= hi)
		{
			nums[p] = temp[i++];
		}
		else if (temp[i] < temp[j])
		{
			nums[p] = temp[i++];
		}
		else if (temp[i] >= temp[j])
		{
			nums[p] = temp[j++];
		}
	}
}
//快速排序：递归的分治过程：时间复杂度nlogn（已知最快的实践排序算法）
int partition(std::vector<int>& nums, int lo, int hi);
void quicksort(std::vector<int>& nums, int lo, int hi)
{
	if (lo >= hi)
	{
		return;
	}
	int p = partition(nums, lo, hi);

	quicksort(nums, lo, p-1);

	quicksort(nums, p + 1, hi);
}
int partition(std::vector<int>& nums, int lo, int hi)
{
	int pivot = nums[lo];
	int i = lo+1, j = hi;
	while (i < j)
	{
		while (i<=hi && nums[i]<pivot)
		{
			i++;
		}
		while (j > lo && nums[j] >= pivot)
		{
			j--;
		}
		if (i < j)
		{
			std::swap(nums[i], nums[j]);
		}
	}
	std::swap(nums[lo], nums[j]);
	return j;
}