#
# Specifies which COM port to connect to:
#   USB picks one
# If you have more than one board connected, disconnect all but the one that you want.
# Load it (Using Run Em-Builder Example) and observe the MSP430Flasher.exe output:
# You should find something like:  "Found USB FET @ HID0xxx:COMxxx". 
# Make note of the HID and COM numbers. 
# Once you know that information, you can plug the other boards back in.
# To select the specific LaunchPad use: COMPORT = HID0xxx:COMxxx
#
COMPORT = USB
#COMPORT = HID0008:COM4
#
# Select one of the boards below by uncommenting one line
#
#BOARD = MSP_EXP430G2
#BOARD = MSP_EXP430F5529LP
#BOARD = MSP_EXP430F5438A
#BOARD = MSP_EXP430FR5739
#BOARD = MSP_EXP430FR5969
