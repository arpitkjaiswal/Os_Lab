#Write a shell script to calculate the gross salary. GS=Basics + TA + 10% of Basics.
#Floating point calculations has to be performed.
 echo "Enter the basic salary"
 read basics

 echo "Enter the travel Allowance (TA):"
 read ta

 ten_percent=$(echo "scale=2; $basics * 0.10" |  bc)
 
 gs=$(echo "scale=2; $basics +$ta + $ten_percent" | bc)

 echo "Gross Salary = $gs"
