# 3Drotations
This repository contains f95, IDL, MatLab, and C++ versions of a 3D rotations conversion library. 
Current development of this package is supported by an AFOSR/MURI grant, **FA9550-12-1-0458**.

The original routines were written in f95 by M. De Graef; the library contains pairwise conversion 
routines for the following rotation representations:
- Euler angles (Bunge zxz setting)
- rotation matrix
- Rodrigues vector
- quaternion
- axis-angle pair
- homochoric vector
- cubochoric vector

The cubochoric representation is new and is fully described in the following publication:

D. Rosca, A. Morawiec, and M. De Graef. “A new method of constructing a grid in the space of 
3D rotations and its applications to texture analysis”. *Modeling and Simulations in Materials 
Science and Engineering* **22**, 075013 (2014). [DOI: http://dx.doi.org/10.1088/0965-0393/22/7/075013]

The rotation conversions and all the sign conventions can be found in the following publication:

D.J. Rowenhorst, A.D. Rollett, G.S. Roher, M.A. Groeber, M.A. Jackson, P.J. Konijnenberg, and 
M. De Graef. "Tutorial: consistent representations of and conversions between 3D rotations". 
*Modeling and Simulations in Materials Science and Engineering* (2015 (in press)).

The scalar IDL version was written by M. De Graef; this version was extended to deal with arrays
of rotations by D. Rowenhorst [NRL].
The MatLab version was created by Amy Wang, then a postdoctoral researcher at CMU.
The C++ version was created from the f95 code by Mike Jackson and Sean Donegan, and is currently part
of the [EbsdLib](https://github.com/bluequartzsoftware/EbsdLib) library and also included in the [DREAM3D](http://www.github.com/bluequartzsoftware/dream3d) package .
