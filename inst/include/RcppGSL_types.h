// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// RcppGSL_types.h: Type macros for Seamless R and GSL Integration
//
// Copyright (C)  2010 - 2015  Romain Francois and Dirk Eddelbuettel
//
// This file is part of RcppGSL.
//
// RcppGSL is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//                           
// RcppGSL is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppGSL.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RCPPGSL_RCPPGSL_SPEC_H
#define RCPPGSL_RCPPGSL_SPEC_H

#undef _RCPPGSL_SPEC
#undef _RCPPGSL_SPEC_NOSUFFIX

#define _RCPPGSL_SPEC(__T__,__SUFFIX__,__CAST__)                        \
template <> struct vector_view_type<__T__> {                            \
    typedef gsl_vector##__SUFFIX__##_view type;                         \
};                                                                      \
template <> struct matrix_view_type<__T__> {                            \
    typedef gsl_matrix##__SUFFIX__##_view type;                         \
};                                                                      \
template <> class vector<__T__>  {           	                        \
public:                                                                 \
    typedef __T__ type;                                                 \
    typedef __T__* pointer;                                             \
    typedef gsl_vector##__SUFFIX__ gsltype;                             \
    gsltype* data;                                                      \
    class Proxy {                                                       \
    public:                                                             \
        Proxy(gsltype* data_, int index_) :                             \
            index(index_), parent(data_) {}                             \
        Proxy& operator=(type x) {                                      \
            gsl_vector##__SUFFIX__##_set(parent, index, x);             \
            return *this;                                               \
        }                                                               \
        inline operator type() {                                        \
            return gsl_vector##__SUFFIX__##_get(parent, index);         \
        }                                                               \
        inline operator const type() const {                            \
            return gsl_vector##__SUFFIX__##_get(parent, index);         \
        }                                                               \
        int index;                                                      \
        gsltype* parent;                                                \
        inline void move(int d) { index += d; }                         \
    };                                                                  \
    class ConstProxy {                                                  \
    public:                                                             \
        ConstProxy(const gsltype* data_, int index_) :                  \
            index(index_), parent(data_) {}                             \
        inline operator type() {                                        \
            return gsl_vector##__SUFFIX__##_get(parent, index);         \
        }                                                               \
        inline operator const type() const {                            \
            return gsl_vector##__SUFFIX__##_get(parent, index);         \
        }                                                               \
        int index;                                                      \
        const gsltype* parent;                                          \
        inline void move(int d) { index += d; }                         \
    };                                                                  \
    typedef ::Rcpp::internal::Proxy_Iterator<Proxy> iterator;           \
    typedef ::Rcpp::internal::Proxy_Iterator<ConstProxy> const_iterator;\
    const static int RTYPE =                                            \
        ::Rcpp::traits::r_sexptype_traits<type>::rtype;                 \
    vector(SEXP x) throw(::Rcpp::not_compatible) :                      \
        data(0), isAllocated(true) {                                    \
        SEXP y = ::Rcpp::r_cast<RTYPE>(x);                              \
        int size = ::Rf_length(y);                                      \
        data = gsl_vector##__SUFFIX__##_calloc(size);                   \
        ::Rcpp::internal::export_range<__CAST__*>(y,                    \
            reinterpret_cast<__CAST__*>(data->data));                   \
    }                                                                   \
    vector(gsltype* x) : data(x), isAllocated(true) {}                  \
    vector(int size) :                                                  \
        data(gsl_vector##__SUFFIX__##_calloc(size)),                    \
        isAllocated(true) {}                                            \
    ~vector() {}                                                        \
    operator gsltype*() { return data; }                                \
    operator const gsltype*() const { return data; }                    \
    gsltype* operator->() const { return data; }                        \
    gsltype& operator*() const { return *data; }                        \
    vector(const vector& x) : data(x.data), isAllocated(true)  {}       \
    vector& operator=(const vector& other) {                            \
        data = other.data;                                              \
        isAllocated = other.isAllocated;                                \
        return *this;                                                   \
    }                                                                   \
    inline Proxy operator[](int i) {                                    \
    	return Proxy(data, i);                                          \
    }                                                                   \
    inline ConstProxy operator[](int i) const {                         \
    	return ConstProxy(data, i);                                     \
    }                                                                   \
    inline iterator begin() { return iterator(Proxy(*this, 0)); }       \
    inline iterator end() { return iterator(Proxy(*this,data->size)); } \
    inline const_iterator begin() const {                               \
        return const_iterator(ConstProxy(*this, 0));                    \
    }                                                                   \
    inline const_iterator end() const {                                 \
        return const_iterator(ConstProxy(*this, data->size));           \
    }                                                                   \
    inline size_t size() const { return data->size; }                   \
    inline void free() {                                                \
        if (isAllocated) {                                              \
            gsl_vector##__SUFFIX__##_free(data);                        \
            isAllocated = false;                                        \
        }                                                               \
    }                                                                   \
private:                                                                \
 bool isAllocated;                                                      \
};                                                                      \
template <> class matrix<__T__>  {           	                        \
public:                                                                 \
   typedef __T__ type;                                                  \
   typedef __T__* pointer;                                              \
   typedef gsl_matrix##__SUFFIX__ gsltype;                              \
   gsltype* data;                                                       \
   const static int RTYPE =                                             \
       ::Rcpp::traits::r_sexptype_traits<type>::rtype;                  \
   class Proxy {                                                        \
   public:                                                              \
      Proxy(gsltype* data_, int row_, int col_) :                       \
          row(row_), col(col_), parent(data_) {}                        \
      Proxy& operator=(type x) {                                        \
          gsl_matrix##__SUFFIX__##_set(parent, row, col, x);            \
          return *this;                                                 \
      }                                                                 \
      inline operator type() {                                          \
          return gsl_matrix##__SUFFIX__##_get(parent, row, col);        \
      }                                                                 \
      inline operator const type() const {                              \
          return gsl_matrix##__SUFFIX__##_get(parent, row, col);        \
      }                                                                 \
      int row;                                                          \
      int col;                                                          \
      gsltype* parent;                                                  \
   };                                                                   \
   class ConstProxy {                                                   \
   public:                                                              \
      ConstProxy(const gsltype* data_, int row_, int col_) :            \
          row(row_), col(col_), parent(data_) {}                        \
      inline operator type() {                                          \
          return gsl_matrix##__SUFFIX__##_get(parent, row, col);        \
      }                                                                 \
      inline operator const type() const {                              \
          return gsl_matrix##__SUFFIX__##_get(parent, row, col);        \
      }                                                                 \
      int row;                                                          \
      int col;                                                          \
      const gsltype* parent;                                            \
   };                                                                   \
   matrix(SEXP x) throw(::Rcpp::not_compatible) :                       \
       data(0), isAllocated(true) { import(x); }                        \
   matrix(gsltype* x) : data(x), isAllocated(true) {}                   \
   matrix(int nrow, int ncol) :                                         \
       data(gsl_matrix##__SUFFIX__##_alloc(nrow, ncol)),                \
       isAllocated(true) {}                                             \
   ~matrix() {}                                                         \
   operator gsltype*() { return data; }                                 \
   operator const gsltype*() const { return data; }                     \
   gsltype* operator->() const { return data; }                         \
   gsltype& operator*() const { return *data; }                         \
   matrix(const matrix& x) : data(x.data), isAllocated(true)  {}        \
   matrix& operator=(const matrix& other) {                             \
       data = other.data;                                               \
       isAllocated = other.isAllocated;                                 \
       return *this;                                                    \
   }                                                                    \
   inline size_t nrow() const { return data->size1; }                   \
   inline size_t ncol() const { return data->size2; }                   \
   inline size_t size() const { return data->size1 * data->size2; }     \
   inline Proxy operator()(int row, int col){                           \
       return Proxy( *this, row, col);                                  \
   }                                                                    \
   inline ConstProxy operator()(int row, int col) const {               \
       return ConstProxy( *this, row, col);                             \
   }                                                                    \
   void free(){                                                         \
       if (isAllocated) {                                               \
           gsl_matrix##__SUFFIX__##_free(data);                         \
           isAllocated = false;                                         \
       }                                                                \
   }                                                                    \
private:                                                                \
   inline void import(SEXP x) throw(::Rcpp::not_compatible);            \
   bool isAllocated;                                                    \
};                                                                      \


#define _RCPPGSL_SPEC_NOSUFFIX(__T__,__CAST__)                          \
template <> struct vector_view_type<__T__> {                            \
    typedef gsl_vector_view type;                                       \
};                                                                      \
template <> struct matrix_view_type<__T__> {                            \
    typedef gsl_matrix_view type;                                       \
};                                                                      \
template <> class vector<__T__>  {           	                        \
public:                                                                 \
   typedef __T__ type;                                                  \
   typedef __T__* pointer;                                              \
   typedef gsl_vector gsltype;                                          \
   gsltype* data;                                                       \
   class Proxy {                                                        \
   public:                                                              \
       Proxy(gsltype* data_, int index_) :                              \
           index(index_), parent(data_) {}                              \
       Proxy& operator=(type x) {                                       \
           gsl_vector_set(parent, index, x);                            \
           return *this;                                                \
       }                                                                \
       inline operator type() {                                         \
           return gsl_vector_get(parent, index);                        \
       }                                                                \
       inline operator const type() const {                             \
           return gsl_vector_get(parent, index);                        \
       }                                                                \
       int index;                                                       \
       gsltype* parent;                                                 \
       inline void move(int d) { index += d; }                          \
   };                                                                   \
   class ConstProxy {                                                   \
   public:                                                              \
       ConstProxy(const gsltype* data_, int index_) :                   \
           index(index_), parent(data_) {}                              \
       inline operator type() {                                         \
           return gsl_vector_get(parent, index);                        \
       }                                                                \
       inline operator const type() const {                             \
           return gsl_vector_get(parent, index);                        \
       }                                                                \
       int index;                                                       \
       const gsltype* parent;                                           \
       inline void move(int d) { index += d; }                          \
   };                                                                   \
   typedef ::Rcpp::internal::Proxy_Iterator<Proxy> iterator;            \
   typedef ::Rcpp::internal::Proxy_Iterator<ConstProxy> const_iterator; \
   const static int RTYPE =                                             \
       ::Rcpp::traits::r_sexptype_traits<type>::rtype;                  \
   vector(SEXP x) throw(::Rcpp::not_compatible) :                       \
       data(0), isAllocated(true) {                                     \
       SEXP y = ::Rcpp::r_cast<RTYPE>(x);                               \
       int size = ::Rf_length(y);                                       \
       data = gsl_vector_calloc(size);                                  \
       ::Rcpp::internal::export_range<__CAST__*>(y,                     \
           reinterpret_cast<__CAST__*>(data->data));                    \
   }                                                                    \
   vector(gsltype* x) : data(x), isAllocated(true) {}                   \
   vector(int size) :                                                   \
       data(gsl_vector_calloc(size)), isAllocated(true) {}              \
   ~vector() {}                                                         \
   operator gsltype*() { return data; }                                 \
   operator const gsltype*() const { return data; }                     \
   gsltype* operator->() const { return data; }                         \
   gsltype& operator*() const { return *data; }                         \
   vector(const vector& x) : data(x.data), isAllocated(true)  {}        \
   vector& operator=(const vector& other) {                             \
       data = other.data;                                               \
       isAllocated = other.isAllocated;                                 \
       return *this;                                                    \
   }                                                                    \
   inline Proxy operator[](int i) {                                     \
       return Proxy(data, i);                                           \
   }                                                                    \
   inline ConstProxy operator[](int i) const {                          \
       return ConstProxy(data, i);                                      \
   }                                                                    \
   inline iterator begin() { return iterator(Proxy(*this, 0)); }        \
   inline iterator end() { return iterator(Proxy(*this, data->size)); } \
   inline const_iterator begin() const {                                \
       return const_iterator(ConstProxy(*this, 0));                     \
   }                                                                    \
   inline const_iterator end() const {                                  \
       return const_iterator(ConstProxy(*this, data->size));            \
   }                                                                    \
   inline size_t size() const { return data->size; }                    \
   inline void free() {                                                 \
       if (isAllocated) {                                               \
           gsl_vector_free(data);                                       \
           isAllocated = false;                                         \
       }                                                                \
   }                                                                    \
private:                                                                \
   bool isAllocated;                                                    \
};                                                                      \
template <> class matrix<__T__>  {                                      \
public:                                                                 \
   typedef __T__ type;                                                  \
   typedef __T__* pointer;                                              \
   typedef gsl_matrix gsltype;                                          \
   gsltype* data;                                                       \
   const static int RTYPE =                                             \
       ::Rcpp::traits::r_sexptype_traits<type>::rtype;                  \
   class Proxy {                                                        \
   public:                                                              \
       Proxy(gsltype* data_, int row_, int col_) :                      \
           row(row_), col(col_), parent(data_) {}                       \
       Proxy& operator=(type x) {                                       \
           gsl_matrix_set(parent, row, col, x);                         \
           return *this;                                                \
       }                                                                \
       inline operator type() {                                         \
           return gsl_matrix_get(parent, row, col);                     \
       }                                                                \
       inline operator const type() const {                             \
           return gsl_matrix_get(parent, row, col);                     \
       }                                                                \
       int row;                                                         \
       int col;                                                         \
       gsltype* parent;                                                 \
   };                                                                   \
   class ConstProxy {                                                   \
   public:                                                              \
       ConstProxy(const gsltype* data_, int row_, int col_) :           \
           row(row_), col(col_), parent(data_) {}                       \
       inline operator type() {                                         \
           return gsl_matrix_get(parent, row, col);                     \
       }                                                                \
       inline operator const type() const {                             \
           return gsl_matrix_get(parent, row, col);                     \
       }                                                                \
       int row;                                                         \
       int col;                                                         \
       const gsltype* parent;                                           \
   };                                                                   \
   matrix(SEXP x) throw(::Rcpp::not_compatible) :                       \
       data(0), isAllocated(true) { import(x); }                        \
   matrix(gsltype* x) : data(x), isAllocated(true) {}                   \
   matrix(int nrow, int ncol) :                                         \
       data(gsl_matrix_alloc(nrow, ncol)), isAllocated(true) {}         \
   ~matrix() {}                                                         \
   operator gsltype*() { return data; }                                 \
   operator const gsltype*() const { return data; }                     \
   gsltype* operator->() const { return data; }                         \
   gsltype& operator*() const { return *data; }                         \
   matrix(const matrix& x) : data(x.data), isAllocated(true) {}         \
   matrix& operator=(const matrix& other) {                             \
       data = other.data;                                               \
       isAllocated = other.isAllocated;                                 \
       return *this;                                                    \
   }                                                                    \
   inline size_t nrow() const { return data->size1; }                   \
   inline size_t ncol() const { return data->size2; }                   \
   inline size_t size() const { return data->size1 * data->size2; }     \
   inline Proxy operator()(int row, int col) {                          \
       return Proxy(*this, row, col);                                   \
   }                                                                    \
   inline ConstProxy operator()(int row, int col) const {               \
       return ConstProxy(*this, row, col);                              \
   }                                                                    \
   void free() {                                                        \
       if (isAllocated) {                                               \
           gsl_matrix_free(data);                                       \
           isAllocated = false;                                         \
       }                                                                \
   }                                                                    \
private:                                                                \
   inline void import(SEXP x) throw(::Rcpp::not_compatible);            \
   bool isAllocated;                                                    \
};                                                                      \

#endif
