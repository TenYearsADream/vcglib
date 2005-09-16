/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
History

$Log: not supported by cvs2svn $
Revision 1.3  2005/09/16 10:03:46  m_di_benedetto
General interface redefinition, added special functors for faces.

Revision 1.2  2005/09/11 11:46:43  m_di_benedetto
First Commit




****************************************************************************/

#ifndef __VCGLIB_AABBBINARYTREEUTILS
#define __VCGLIB_AABBBINARYTREEUTILS

// vcg headers
#include <vcg/space/point3.h>
#include <vcg/space/box3.h>


/***************************************************************************************/

namespace vcg {

/*

Class AABBBinaryTreeUtils

SAMPLE USAGE:

NOTES:

*/

template <class SCALARTYPE, class OBJTYPE>
class AABBBinaryTreeUtils {
	public:
		typedef AABBBinaryTreeUtils<SCALARTYPE, OBJTYPE> ClassType;
		typedef SCALARTYPE ScalarType;
		typedef OBJTYPE ObjType;

	protected:
		template <class T1, class T2>
		class P3Converter {
		public:
			static Point3<T1> Convert(const Point3<T2> & p) {
				return Point3<T1>( (T1)p[0], (T1)p[1], (T1)p[2] );
      }
		};

		template <class T>
		class P3Converter<T, T> {
		public:
			static Point3<T> Convert(const Point3<T> & p) {
				return (p);
      }
		};

	public:

		template <class S, class T>
		static Point3<S> ConvertP3(const Point3<T> & p) {
			return (ClassType::P3Converter<S, T>::Convert(p));
		}

		class Face {
		};

		class EmptyClass {
		};

	
		class ObjIteratorPtrFunct {
			public:
					  template <class T>
            inline T * operator () (T & t) {
				      return (&t);
            }
            template <class T *>
            inline T * operator () (T* & t) {
				      return (t);
				    }

		};

		static ObjIteratorPtrFunct IteratorPtrFunctor(void) {
      ObjIteratorPtrFunct pp;
			return pp;
		}

		template <class OBJ>
		class ObjBoxFunct {
			public:
				inline Box3<ScalarType> operator () (const OBJ & obj) {
					(void)obj;
					Box3<ScalarType> box;
					box.SetNull();
					return (box);
				}
		};

			static ObjBoxFunct<ObjType> BoxFunctor(void) {
      ObjBoxFunct<ObjType> tt;
			return tt;
		}

		template <class FACETYPE>
		class FaceBoxFunct {
			public:
				typedef FACETYPE FaceType;
				inline Box3<ScalarType> operator () (const FaceType & f) {
					Box3<ScalarType> box;
					box.Set(ConvertP3<ScalarType, FaceType::ScalarType>(f.P(0)));
					box.Add(ConvertP3<ScalarType, FaceType::ScalarType>(f.P(1)));
					box.Add(ConvertP3<ScalarType, FaceType::ScalarType>(f.P(2)));
					return (box);
				}
		};

		template <class FACETYPE>
		static FaceBoxFunct<FACETYPE> FaceBoxFunctor(void) {
      FaceBoxFunct<FACETYPE> tt;
			return tt;
		}

		template <class OBJ>
		class ObjBarycenterFunct {
			public:
				inline Point3<ScalarType> operator () (const OBJ & obj) {
					(void)obj;
					printf("GENERAL\n");
					Point3<ScalarType> bc(ScalarType(0), ScalarType(0), ScalarType(0));
					return (bc);
				}
		};


		static ObjBarycenterFunct<ObjType> BarycenterFunctor(void) {
      ObjBarycenterFunct<ObjType> tt;
			return tt;
		}

		template <class FACETYPE>
		class FaceBarycenterFunct {
			public:
				typedef FACETYPE FaceType;
				inline Point3<ScalarType> operator () (const FaceType & f) {
					return (ConvertP3<ScalarType, FaceType::ScalarType>(f.Barycenter()));
				}
		};

		template <class FACETYPE>
		static FaceBarycenterFunct<FACETYPE> FaceBarycenterFunctor(void) {
      FaceBarycenterFunct<FACETYPE> tt;
			return tt;
		}

		template <class OBJ>
		class ObjPointDistanceFunct {
			public:
				inline bool operator () (const OBJ & obj, const Point3<ScalarType> & p, ScalarType & minDist, Point3<ScalarType> & res) {
					(void)obj;
					(void)p;
					(void)minDist;
					(void)res;
					return (false);
				}
		};

	
		static ObjPointDistanceFunct<ObjType> PointDistanceFunctor(void) {
      ObjPointDistanceFunct<ObjType> tt;
			return tt;
		}

		template <class FACETYPE>
		class FacePointDistanceFunct {
			public:
				typedef FACETYPE FaceType;
				inline bool operator () (const FaceType & f, const Point3<ScalarType> & p, ScalarType & minDist, Point3<ScalarType> & res) {
					Point3<ScalarType> fp = ConvertP3<FaceType::ScalarType, ScalarType>(p);
					typename FaceType::ScalarType md = (typename FaceType::ScalarType)minDist;
					Point3<ScalarType> fres;
					const bool bret = face::PointDistance(f, p, md, fres);
					minDist = ScalarType(md);
					res = ConvertP3<ScalarType, typename FaceType::ScalarType>(fres);
					return (bret);
				}
		};

		template <class FACETYPE>
		static FacePointDistanceFunct<FACETYPE> FacePointDistanceFunctor(void) {
      FacePointDistanceFunct<FACETYPE> tt;
			return tt;
		}

};

/***************************************************************************************/

}	// end namespace vcg

#endif // #ifndef __VCGLIB_AABBBINARYTREEUTILS
