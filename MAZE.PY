def rotate(nums, k):
    for i in range(k):
        p = nums[i]
        if k >= len(nums):
            return nums
        elif k > (len(nums)//2):
            nums[i] = nums[len(nums)-k]
            nums[len(nums)-k] = nums[k+i]
            nums[k+i] = p
        else:
            nums[i] = nums[len(nums)-k+i]
            nums[len(nums)-k+i] = nums[k+i]
            nums[k+i] = p
    return nums

nums = [1,2,3,4,5,6,7]
k = 4
print(rotate(nums, k))