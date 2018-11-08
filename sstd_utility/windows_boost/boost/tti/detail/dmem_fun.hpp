﻿
//  (C) Copyright Edward Diener 2011,2012,2013
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_MEM_FUN_HPP)
#define BOOST_TTI_DETAIL_MEM_FUN_HPP

#include <boost/config.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/tti/detail/dcomp_mem_fun.hpp>
#include <boost/tti/detail/ddeftype.hpp>
#include <boost/tti/detail/dnullptr.hpp>
#include <boost/tti/detail/dptmf.hpp>
#include <boost/tti/gen/namespace_gen.hpp>

#if defined(__SUNPRO_CC)

#define BOOST_TTI_DETAIL_TRAIT_HAS_TYPES_MEMBER_FUNCTION(trait,name) \
  template<class BOOST_TTI_DETAIL_TP_PMEMF,class BOOST_TTI_DETAIL_TP_C> \
  struct BOOST_PP_CAT(trait,_detail_types) \
    { \
    template<BOOST_TTI_DETAIL_TP_PMEMF> \
    struct helper {}; \
    \
    template<class BOOST_TTI_DETAIL_TP_EC> \
    static ::boost::type_traits::yes_type chkt(helper<&BOOST_TTI_DETAIL_TP_EC::name> *); \
    \
    template<class BOOST_TTI_DETAIL_TP_EC> \
    static ::boost::type_traits::no_type chkt(...); \
    \
    typedef boost::mpl::bool_<sizeof(chkt<BOOST_TTI_DETAIL_TP_C>(BOOST_TTI_DETAIL_NULLPTR))==sizeof(::boost::type_traits::yes_type)> type; \
    }; \
/**/

#else

#define BOOST_TTI_DETAIL_TRAIT_HAS_TYPES_MEMBER_FUNCTION(trait,name) \
  template<class BOOST_TTI_DETAIL_TP_PMEMF,class BOOST_TTI_DETAIL_TP_C> \
  struct BOOST_PP_CAT(trait,_detail_types) \
    { \
    template<BOOST_TTI_DETAIL_TP_PMEMF> \
    struct helper; \
    \
    template<class BOOST_TTI_DETAIL_TP_EC> \
    static ::boost::type_traits::yes_type chkt(helper<&BOOST_TTI_DETAIL_TP_EC::name> *); \
    \
    template<class BOOST_TTI_DETAIL_TP_EC> \
    static ::boost::type_traits::no_type chkt(...); \
    \
    typedef boost::mpl::bool_<sizeof(chkt<BOOST_TTI_DETAIL_TP_C>(BOOST_TTI_DETAIL_NULLPTR))==sizeof(::boost::type_traits::yes_type)> type; \
    }; \
/**/

#endif

#define BOOST_TTI_DETAIL_TRAIT_CTMF_INVOKE(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_TYPES_MEMBER_FUNCTION(trait,name) \
  template<class BOOST_TTI_DETAIL_TP_T,class BOOST_TTI_DETAIL_TP_R,class BOOST_TTI_DETAIL_TP_FS,class BOOST_TTI_DETAIL_TP_TAG> \
  struct BOOST_PP_CAT(trait,_detail_ctmf_invoke) : \
    BOOST_PP_CAT(trait,_detail_types) \
      < \
      typename BOOST_TTI_NAMESPACE::detail::ptmf_seq<BOOST_TTI_DETAIL_TP_T,BOOST_TTI_DETAIL_TP_R,BOOST_TTI_DETAIL_TP_FS,BOOST_TTI_DETAIL_TP_TAG>::type, \
      BOOST_TTI_DETAIL_TP_T \
      > \
    { \
    }; \
/**/

#define BOOST_TTI_DETAIL_TRAIT_HAS_CALL_TYPES_MEMBER_FUNCTION(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_CTMF_INVOKE(trait,name) \
  template<class BOOST_TTI_DETAIL_TP_T,class BOOST_TTI_DETAIL_TP_R,class BOOST_TTI_DETAIL_TP_FS,class BOOST_TTI_DETAIL_TP_TAG> \
  struct BOOST_PP_CAT(trait,_detail_call_types) : \
	boost::mpl::eval_if \
		< \
 		boost::is_class<BOOST_TTI_DETAIL_TP_T>, \
 		BOOST_PP_CAT(trait,_detail_ctmf_invoke) \
 			< \
 			BOOST_TTI_DETAIL_TP_T, \
 			BOOST_TTI_DETAIL_TP_R, \
 			BOOST_TTI_DETAIL_TP_FS, \
 			BOOST_TTI_DETAIL_TP_TAG \
 			>, \
 		boost::mpl::false_ \
		> \
    { \
    }; \
/**/

#define BOOST_TTI_DETAIL_TRAIT_CHECK_HAS_COMP_MEMBER_FUNCTION(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_COMP_MEMBER_FUNCTION(trait,name) \
  template<class BOOST_TTI_DETAIL_TP_T> \
  struct BOOST_PP_CAT(trait,_detail_check_comp) : \
    BOOST_PP_CAT(trait,_detail_hcmf)<BOOST_TTI_DETAIL_TP_T> \
    { \
    BOOST_MPL_ASSERT((boost::function_types::is_member_function_pointer<BOOST_TTI_DETAIL_TP_T>)); \
    }; \
/**/

#define BOOST_TTI_DETAIL_TRAIT_HAS_MEMBER_FUNCTION(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_CALL_TYPES_MEMBER_FUNCTION(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_CHECK_HAS_COMP_MEMBER_FUNCTION(trait,name) \
  template<class BOOST_TTI_DETAIL_TP_T,class BOOST_TTI_DETAIL_TP_R,class BOOST_TTI_DETAIL_TP_FS,class BOOST_TTI_DETAIL_TP_TAG> \
  struct BOOST_PP_CAT(trait,_detail_hmf) : \
    boost::mpl::eval_if \
      < \
      boost::mpl::and_ \
        < \
        boost::is_same<BOOST_TTI_DETAIL_TP_R,BOOST_TTI_NAMESPACE::detail::deftype>, \
        boost::is_same<BOOST_TTI_DETAIL_TP_FS,boost::mpl::vector<> >, \
        boost::is_same<BOOST_TTI_DETAIL_TP_TAG,boost::function_types::null_tag> \
        >, \
      BOOST_PP_CAT(trait,_detail_check_comp)<BOOST_TTI_DETAIL_TP_T>, \
      BOOST_PP_CAT(trait,_detail_call_types)<BOOST_TTI_DETAIL_TP_T,BOOST_TTI_DETAIL_TP_R,BOOST_TTI_DETAIL_TP_FS,BOOST_TTI_DETAIL_TP_TAG> \
      > \
    { \
    }; \
/**/

#endif // BOOST_TTI_DETAIL_MEM_FUN_HPP
