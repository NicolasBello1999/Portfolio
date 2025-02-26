import ctypes

# Load the DLL
dll_path = "NgSocialNet.dll"
ngsocial_dll = ctypes.WinDLL(dll_path)

# Declare the function without specifying arguments (start simple)
ngsocial_net_http_request = ngsocial_dll.ngsocial_net_http_request

# Try calling the function with dummy arguments
try:
    result = ngsocial_net_http_request("None")  # Start with `None` or basic test
    print(f"Function result: {result}")
except Exception as e:
    print(f"Error occurred: {e}")
