! ###################################################################
! Copyright (c) 2015, Marc De Graef/Carnegie Mellon University
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
! EMsoft:constants.f90
!--------------------------------------------------------------------------
!
! MODULE: constants
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief 
!> Definition of constants and constant arrays used by other routines
!
!> @details  
!> physical and mathematical constants used by various programs; periodic
!>  table information; atomic weights; 
! 
!> @date 1/5/99   MDG 1.0 original
!> @date 5/18/01  MDG 2.0 f90
!> @date 11/27/01 MDG 2.1 added kind support
!> @date 03/19/13 MDG 3.0 added atomic weights 
!> @date 01/10/14 MDG 4.0 new version
!> @date 04/29/14 MDG 4.1 constants updated from NIST physical constants tables
!> @date 07/06/14 MDG 4.2 added omegamax to Lambert constant type
!> @date 08/11/14 MDG 4.3 added infty for handling of +Infinity in rotations module
!> @date 08/11/14 MDG 4.4 added epsijk option to package
!> @date 09/30/14 MDG 4.5 added some additional comments about epsijk
!> @date 10/02/14 MDG 4.6 removed omegamax again, since we now have properly dealt with 180 degree rotations
!> @date 03/11/15 MDG 4.7 added some additional comments about epsijk 
!--------------------------------------------------------------------------

module constants

use local

IMPLICIT NONE

! ****************************************************
! ****************************************************
! ****************************************************
! used to change the sign of the permutation symbol from Adam Morawiec's book to
! the convention used for the EMsoft package.  If you want to use Adam's convention,
! both of these parameters should be set to +1; -1 will change the sign everywhere
! for all representations that involve the unit vector.  The quaternion product is 
! also redefined to include the epsijk parameter.  Doing so guarantees that the 
! quat_Lp operator ALWAYS returns an active result, regardless of the choice of epsijk;
! quat_LPstar ALWAYS returns a passive result.

! Uncomment these for an alternative way of doing things
!real(kind=sgl), parameter :: epsijk = -1.0
!real(kind=dbl), parameter :: epsijkd = -1.D0

! uncomment these for the Morawiec version.
real(kind=sgl), parameter :: epsijk = 1.0
real(kind=dbl), parameter :: epsijkd = 1.D0

! In the first case, epsijk=-1, the rotation 120@[111] will result in 
! an axis angle pair of [111], 2pi/3.  In the second case, the axis-angle 
! pair will be -[111], 2pi/3.  In all cases, the rotations are interpreted
! in the passive sense.  The case epsijk=+1 corresponds to the mathematically 
! consistent case, using the standard definition for the quaternion product; in
! the other case, epsijk=-1, one must redefine the quaternion product in order
! to produce consistent results.  This takes a lengthy explanation ... see the
! rotations tutorial paper for an in-depth explanation.  These changes propagate
! to a number of files, notably quaternions.f90, and everywhere else that quaternions
! and rotations in general are used.
! ****************************************************
! ****************************************************
! ****************************************************

! the rotations.f90 routines need to have access to the value +Infinity
! which is defined here (using the LaTeX name infty)
INTEGER,private :: inf
REAL,public :: infty
EQUIVALENCE (inf,infty) ! stores two variable at the same address
DATA inf/z'7f800000'/ !Hex for +Infinity

INTEGER(kind=8),private :: infd
REAL(kind=dbl),public :: inftyd
EQUIVALENCE (infd,inftyd) ! stores two variable at the same address
DATA infd/z'7FF0000000000000'/ !Hex for +Infinity



! various physical constants

real(kind=dbl), parameter :: cPi=3.141592653589793238D0

! these are a bunch of constants used for Lambert and related projections; they are all in double precision
type LambertParametersType
        real(kind=dbl)          :: Pi=3.141592653589793D0       !  pi
        real(kind=dbl)          :: iPi=0.318309886183791D0      !  1/pi
        real(kind=dbl)          :: sPi=1.772453850905516D0      !  sqrt(pi)
        real(kind=dbl)          :: sPio2=1.253314137315500D0    !  sqrt(pi/2)
        real(kind=dbl)          :: sPi2=0.886226925452758D0     !  sqrt(pi)/2
        real(kind=dbl)          :: srt=0.866025403784439D0      !  sqrt(3)/2
        real(kind=dbl)          :: isrt=0.577350269189626D0    !  1/sqrt(3)
        real(kind=dbl)          :: alpha=1.346773687088598D0   !  sqrt(pi)/3^(1/4)
        real(kind=dbl)          :: rtt=1.732050807568877D0      !  sqrt(3)
        real(kind=dbl)          :: prea=0.525037567904332D0    !  3^(1/4)/sqrt(2pi)
        real(kind=dbl)          :: preb=1.050075135808664D0     !  3^(1/4)sqrt(2/pi)
        real(kind=dbl)          :: prec=0.906899682117109D0    !  pi/2sqrt(3)
        real(kind=dbl)          :: pred=2.094395102393195D0     !  2pi/3
        real(kind=dbl)          :: pree=0.759835685651593D0     !  3^(-1/4)
        real(kind=dbl)          :: pref=1.381976597885342D0     !  sqrt(6/pi)
! the following constants are used for the cube to quaternion hemisphere mapping
        real(kind=dbl)          :: a=1.925749019958253D0        ! pi^(5/6)/6^(1/6)
        real(kind=dbl)          :: ap=2.145029397111025D0       ! pi^(2/3)
        real(kind=dbl)          :: sc=0.897772786961286D0       ! a/ap
        real(kind=dbl)          :: beta=0.962874509979126D0     ! pi^(5/6)/6^(1/6)/2
        real(kind=dbl)          :: R1=1.330670039491469D0       ! (3pi/4)^(1/3)
        real(kind=dbl)          :: r2=1.414213562373095D0       ! sqrt(2)
        real(kind=dbl)          :: r22=0.707106781186547D0      ! 1/sqrt(2)
        real(kind=dbl)          :: pi12=0.261799387799149D0     ! pi/12
        real(kind=dbl)          :: pi8=0.392699081698724D0      ! pi/8
        real(kind=dbl)          :: prek=1.643456402972504D0     ! R1 2^(1/4)/beta
        real(kind=dbl)          :: r24=4.898979485566356D0      ! sqrt(24)
        real(kind=dbl)          :: tfit(16) = (/1.0000000000018852D0, -0.5000000002194847D0, & 
                                             -0.024999992127593126D0, - 0.003928701544781374D0, & 
                                             -0.0008152701535450438D0, - 0.0002009500426119712D0, & 
                                             -0.00002397986776071756D0, - 0.00008202868926605841D0, & 
                                             +0.00012448715042090092D0, - 0.0001749114214822577D0, & 
                                             +0.0001703481934140054D0, - 0.00012062065004116828D0, & 
                                             +0.000059719705868660826D0, - 0.00001980756723965647D0, & 
                                             +0.000003953714684212874D0, - 0.00000036555001439719544D0 /)
	real(kind=dbl)              :: BP(6)= (/ 0.D0, 1.D0, 0.577350269189626D0, 0.414213562373095D0, 0.D0,  &
                                              0.267949192431123D0 /)       ! used for Fundamental Zone determination in so3 module
end type LambertParametersType

type(LambertParametersType)        :: LPs


! The following two arrays are used to determine the FZtype (FZtarray) and primary rotation axis order (FZoarray)
! for each of the 32 crystallographic point group symmetries (in the order of the International Tables)
!
! 1 (C1), -1 (Ci), [triclinic]
! 2 (C2), m (Cs), 2/m (C2h), [monoclinic]
! 222 (D2), mm2 (C2v), mmm (D2h), [orthorhombic]
! 4 (C4), -4 (S4), 4/m (C4h), 422 (D4), 4mm (C4v), -42m (D2d), 4/mmm (D4h), [tetragonal]
! 3 (C3), -3 (C3i), 32 (D3), 3m (C3v), -3m (D3d), [trigonal]
! 6 (C6), -6 (C3h), 6/m (C6h), 622 (D6), 6mm (C6v), -6m2 (D3h), 6/mmm (D6h), [hexagonal]
! 23 (T), m3 (Th), 432 (O), -43m (Td), m-3m (Oh) [cubic]
!
! FZtype
! 0        no symmetry at all
! 1        cyclic symmetry
! 2        dihedral symmetry
! 3        tetrahedral symmetry
! 4        octahedral symmetry
!
! these parameters are used in the so3 module
!
integer(kind=irg),parameter     :: FZtarray(32) = (/ 0,0,1,1,1,2,2,2,1,1,1,2,2,2,2,1,1,2,2,2,1,1,1,2,2,2,2,3,3,4,3,4 /)
integer(kind=irg),parameter     :: FZoarray(32) = (/ 0,0,2,2,2,2,2,2,4,4,4,4,4,4,4,3,3,3,3,3,6,6,6,6,6,6,6,0,0,0,0,0 /)


end module
