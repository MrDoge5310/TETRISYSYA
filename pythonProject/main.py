def checkPalindrome(number: object) -> object:
    """checking"""
    numbers_list = list(number)
    reversed_list = list(reversed(number))
    if numbers_list == reversed_list:
        print("The number is palindrome")
    else:
        print("The number isn't palindrome")


num = input("Input a number: ")
if not num.isdigit():
    exit("wrong input")
else:
    checkPalindrome(num)
