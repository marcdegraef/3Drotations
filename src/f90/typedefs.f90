! ###################################################################
! Copyright (c) 2014, Marc De Graef/Carnegie Mellon University
! All rights reserved.
!
! Redistribution and use in source and binary forms, with or without modification, are 
! permitted provided that the following conditions are met:
!
!     - Redistributions of source code must retain the above copyright notice, this list 
!        of conditions and the following disclaimer.
!     - Redistributions in binary form must reproduce the above copyright notice, this 
!        list of conditions and the following disclaimer in the documentation and/or 
!        other materials provided with the distribution.
!     - Neither the names of Marc De Graef, Carnegie Mellon University nor the names 
!        of its contributors may be used to endorse or promote products derived from 
!        this software without specific prior written permission.
!
! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
! DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
! SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
! CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
! OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
! USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
! ###################################################################

!--------------------------------------------------------------------------
! CTEMsoft:typedefs.f90
!--------------------------------------------------------------------------
!
! MODULE: typedefs
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief Definition of all variables and types for crystallographic computations
!
!> @details  Defines the unitcell type and the orientation type, as well as 
!> the main cell variable used by all crystallographic computations
! 
!> @date     1/5/99 MDG 1.0 original
!> @date    7/16/99 MDG 1.1 added error handling and TransCoor
!> @date    4/ 5/00 MDG 1.2 modified TransCoor to include new mInvert
!> @date    5/19/01 MDG 2.0 f90 version
!> @date   03/19/13 MDG 3.0 update to new version
!> @date   10/17/13 MDG 3.1 added HOLZentries type
!> @date    1/10/14 MDG 4.0 new version, many new entries in unitcell type
!> @date    6/ 5/14 MDG 4.1 removed variable declaration for cell
!> @date    6/ 9/14 MDG 4.2 added all defect type declarations
!> @date    8/11/14 MDG 4.3 modified Rodrigues vector to 4 components
!> @date   12/02/14 MDG 4.4 added a few entries to unitcell pointer
!--------------------------------------------------------------------------
module typedefs

use local

!--------------------------------------------------------------------------
!--------------------------------------------------------------------------
!--------------------------------------------------------------------------

! the "orientation" type contains entries for all rotation and orientation representations
type orientationtype
  real(kind=sgl)        :: eulang(3)            ! Bunge Euler angles in radians
  real(kind=sgl)        :: om(3,3)              ! 3x3 matrix
  real(kind=sgl)        :: axang(4)             ! axis-angle pair (angle in rad, component 4; axis in direction cosines)
  real(kind=sgl)        :: rodrigues(4)         ! Rodrigues vector (stored as direction cosines and length, to allow for Infinity)
  real(kind=sgl)        :: quat(4)              ! quaternion representation (q(1) is scalar part, q(2:4) vector part)
  real(kind=sgl)        :: homochoric(3)        ! homochoric representation according to Frank's paper  
  real(kind=sgl)        :: cubochoric(3)        ! cubic grid representation (derived from homochoric)
end type orientationtype


! double precision version
type orientationtyped
  real(kind=dbl)        :: eulang(3)            ! Bunge Euler angles in radians
  real(kind=dbl)        :: om(3,3)              ! 3x3 matrix
  real(kind=dbl)        :: axang(4)             ! axis-angle pair (angle in rad, component 4; axis in direction cosines)
  real(kind=dbl)        :: rodrigues(4)         ! Rodrigues vector (stored as direction cosines and length, to allow for Infinity)
  real(kind=dbl)        :: quat(4)              ! quaternion representation (q(1) is scalar part, q(2:4) vector part)
  real(kind=dbl)        :: homochoric(3)        ! homochoric representation according to Frank's paper  
  real(kind=dbl)        :: cubochoric(3)        ! cubic grid representation (derived from homochoric)
end type orientationtyped


end module typedefs
