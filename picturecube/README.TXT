
The TJPEGImage class in C++Builder 3

Special notes

When using TJPEGImage in a project that does not use runtime packages you may need to include the following code:

	#if !defined(USEPACKAGES)
		FakeInitJPEGLib();
	#endif

This will force the unit to be initialized. This is only necessary for extremely simple uses 
of TJPEGImage.


Usage:
Distributed with this document is an example named JPEGDEMO. This demo should illustrate the 
proper use of TJPEGImage. See the instruction below on building the necessary support files for this example.


How it works:
The TJPEGImage class wraps the IJG JPEG library. It registers itself with the graphics subsystem of the VCL in the
 unit initialization section. This registration allows other components to use JPEG images in a way which is
 transparent to both the user and programmer.


Installation:
To use TJPEGImage you must install the package into C++Builder 3. The rules that apply to this package are
no different from other packages. Namely, the BPL file must exist in the path if you are using runtime packages.

From the main menu of C++Builder choose Component | Install Packages...

There are no components in this package. TJPEGImage works with the VCL graphics subsystem. 
Please see the example JPEGDEMO for more information.


How to rebuild everything:
1. cd jpeg/src, make -DDELPHI
2. cd jpeg/package, make -f jpegpkg.bpk
3. Copy jpegpkg.lib, jpegpkg.bpi to C++Builder\lib. Copy jpegpkg.bpl to C++Builder\bin. (Since there are no components
in the package, C++Builder will not automatically add the path information to your project, as it does will other conmponents)
Copy jpeg.hpp to C++Builder\include\vcl.

In the jpeg\src directory you will find a make file. Provided you leave the directory structure as it was originally, 
running make -DDELPHI will create versions of the IJG OBJ files which are compatible with jpeg.pas. The make
process should copy these OBJ files to jpeg\package. 
In the jpeg\package directory you should run make -f jpegpkg.bpk.
After following these simple instructions you should have a rebuilt version of the package containing TJPEGImage. 
