/**
 * @file Kdtree.hpp
 * @brief An implementation of Kd-tree.
 * @author Takashi Michikawa (RCAST, The University of Tokyo)
 * @date 091010 michi Created.
 */
#ifndef __MI_KDTREE_HPP__
#define __MI_KDTREE_HPP__ 1
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

// need :
// T::operator[](int)
    /**
     * @class Kdtree
     * @brief template class for implementing kd-tree.
     * @note You can integrate with any own vector types, but it must have  following two methods:
     * @li T::operator[](int);
     * @li T::T(const T& d);
     * @li T::copy( const T& d) copying entity of d.
     */
    template <typename T, size_t Dim = 3>
    class Kdtree
    {
    public:
            /**
              * @class Vector
              * @brief An implementation of Points with id.
              * Use this if you want to know the id of vertices in Kd-Tree.
              * @note
              * Template class must define = operator
              */
            class Vector : public T
            {
            private:
                    int _id;
            public:
                    Vector( const T& v, const int id ) : T(v) {
                            this->_id = id;
                            return;
                    }
                    Vector( const Vector& d) {
                            this->copy(d);
                            return;
                    }
                    Vector& operator = (const Vector& d) {
                            this->copy(d);
                            return *this;
                    }
                    /**
                      * @brief get id of the point.
                      * @return ID of the point.
                      */
                    int id( void ) const {
                            return this->_id;
                    }
            protected:
                    void copy( const Vector& d) {
                        T::operator=(d);
                            this->_id = d._id;
                            return;
                    }
            };
    private:
            /**
              * @class less_vec_length
              * @brief functor class for comparing two vector used in Kdtree.
              */
            class less_vec_length
            {
            private:
                    T _x;
            public:
                    less_vec_length( const T x ) : _x(x) {
                            return;
                    }
                    bool operator () (const T& a, const T& b) const  {
                            double ra = 0;
                            double rb = 0;
                            for ( size_t i  = 0 ; i  < Dim ; i++) {
                                    ra += (a[i] - this->_x[i])*(a[i] - this->_x[i]);
                                    rb += (b[i] - this->_x[i])*(b[i] - this->_x[i]);
                            }
                            return ra < rb ;
                    }
            };
            /**
              * @class node in kdtree
              */
            class Node
            {
            private:
                    class less_vec_coord
                    {
                    public:
                            char _dim;
                            less_vec_coord(const char dim) : _dim(dim) {
                                    return;
                            }
                            bool operator()(const T &a, const T &b) const {
                                    return a[_dim] < b[_dim];
                            }
                    };
            private:
                    char		_dim;
                    std::list<T> 	_list;
                    Node* 	_child;
            public:
                    Node( void ) {
                            this->_child = NULL;
                            this->_dim = -1;
                            this->_list.clear();
                            return;
                    }

                    Node ( const Node& d) {
                            this->copy(d);
                            return;
                    }
                    Node& operator = (const Node& d) {
                            this->copy(d);
                            return *this;
                    }

                    void copy (const Node& d) {
                            this->_dim =  d._dim;
                            this->_list.clear();
                            this->_list.insert( this->_list.end(), d._list.begin(), d._list.end());

                            if ( !this->isLeaf()) {
                                    this->_child = new Node[2];
                                    for ( size_t i = 0 ; i < 2 ; i++ ) this->_child[i].copy( d._child[i] );
                            }
                            return;
                    }

                    virtual ~Node( void) {
                            this->removeChild();
                            return;
                    }

                    bool init(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, const size_t numMaxNode, const char dim) {
                            this->_list.clear();
                            const size_t num_element = std::distance(begin, end);
                            if (num_element <= numMaxNode) {
                                    for ( typename std::vector<T>::iterator iter = begin ; iter != end ; iter++) this->_list.push_back(*iter);
                            } else {
                                    this->_dim = dim;

                                    std::sort(begin, end, less_vec_coord(this->_dim)); //sort elements by a specific coord.
                                    typename std::vector<T>::iterator center = begin + static_cast<size_t>(num_element/2);
                                    this->_list.push_back(*center);

                                    const char nextdim = this->get_new_dimension();
                                    this->_child = new Node[2];
                                    this->_child[0].init(begin , center, numMaxNode, nextdim );
                                    this->_child[1].init(center, end   , numMaxNode, nextdim );
                            }
                            return true;
                    }

                    char get_new_dimension( void ) const {
                            return ( this->_dim + 1 ) % Dim;
                    }
                    /**
                     * @return a node at the node.
                     */
                    bool isLeaf(void) const {
                            return this->_dim == -1;
                    }
                    /**
                     * @param[in] dp Center of 3D point (dp[0], dp[1], dp[2]).
                     * @param[in] radius Radius of a sphere.
                     * @param[out] result resutl of the points.
                     */
                    void find(const T &pnt, const double radius, typename std::list<T>& result) {
                            if (this->_list.empty()) return;
                            if (this->isLeaf()) {
                                    typename std::list<T>::iterator iter;
                                    const double sqr = radius * radius;
                                    for (iter = this->_list.begin() ; iter != this->_list.end() ; iter++) {
                                            double check = 0;
                                            for ( size_t i = 0 ; i < Dim ; i++) check += (iter->operator[](i) - pnt[i])*(iter->operator[](i) - pnt[i]);
                                            if ( check <= sqr )  result.push_back(*iter);
                                    }
                            } else {
                                    const double p = this->_list.begin()->operator[](this->_dim);
                                    const double x = pnt[this->_dim];
                                    if ( fabs(x-p) <= radius ) {
                                            this->_child[0].find(pnt, radius, result);
                                            this->_child[1].find(pnt, radius, result);
                                    } else {
                                            if ( x < p )this->_child[0].find(pnt, radius, result);
                                            else        this->_child[1].find(pnt, radius, result);
                                    }
                            }
                            return;
                    }

                    void add(const T& p, const size_t numMinNode) {
                            if (this->isLeaf()) {
                                    this->_list.push_back(p);
                                    // if num. of elements in one node exceeds maximum. create new node there.
                                    if ( this->_list.size() > numMinNode ) {
                                            std::vector<T> nodes(this->_list.begin(), this->_list.end());
                                            this->_list.clear();
                                            const char newdim = static_cast<char>(rand() % Dim);
                                            this->init(nodes.begin(), nodes.end(), numMinNode, newdim);
                                            nodes.clear();
                                    }
                            } else {
                                    const double delim = this->_list.begin()->operator[](this->_dim);
                                    const double x = p[this->_dim];
                                    if (x < delim ) this->_child[0].add(p, numMinNode);
                                    else            this->_child[1].add(p, numMinNode);
                            };
                            return;
                    };


                    void removeChild( void ) {
                            if (this->_child != NULL) delete[] this->_child;
                    }
                    /**
                      * @brief get all elements in the tree.
                      */
                    void getAll( std::vector<T>& point) {
                            if ( this->isLeaf()) {
                                    point.insert(point.end(), this->_list.begin(), this->_list.end());
                            } else {
                                    this->_child[0].getAll(point);
                                    this->_child[1].getAll(point);
                            }
                            return;
                    }
            };
    private:
            size_t  _numElement; 	///< A number of points
            size_t  _numMaxElement; ///< maximim num. of elements per node.
            Node _parent;		///< parent node
    public:
            Kdtree( void ) {
                    this->_numElement = 0;
                    return;
            }

            /**
             * @param[in] point point set
             * @param[in] numMinMode maxinum num. of element per node.
             */
            Kdtree(std::vector<T>& point, const size_t numMinNode = 10) {
                    this->build(point, numMinNode);
                    return;
            }

            virtual ~Kdtree( void ) {
                    return;
            }

            /**
             * @param[in] point a input point set
             * @param[in] numMinNode a minimum number of points per node.
             * @retval true Succeeded.
             * @retval false Failed.
             *
             */
            bool build(std::vector<T>& point, const size_t numMinNode = 10) {
                    this->_numMaxElement = numMinNode;
                    this->_numElement = point.size();
                    return this->_parent.init(point.begin(), point.end(), numMinNode, static_cast<char>(0));
            }

            /**
             * @brief Rebuild kd-tree.
             * @param[in] numMinNode a minimum number of points per node.
             * @retval true Succeeded.
             * @retval false Failed.
             */
            bool rebuild ( const size_t numMinNode = 10) {
                    std::vector<T> point;
                    point.reserve( this->size());
                    this->_parent.getAll(point);
                    this->_parent.removeChild();
                    return this->build(point, numMinNode);
            }
            /**
             * @param[in] p position.
             * @param[in] radius a radius of initial sphere.
             * @param[out] node result.
             * @param[in] isSorted
             */
            void find(const T p, const double radius, std::list<T>& node, bool isSorted = false) {
                    node.clear();
                    this->_parent.find(p, radius, node);
                    if (isSorted) node.sort(less_vec_length(p));
                    return;
            }

            /**
             * @param[in] p position.
             * @param[in] num a number of node which you want
             * @param[out] node result.
             * @param[in] radius a radius of initial sphere.
             */
            void find(const T p, const size_t num, std::list<T>& node, double radius = 0.1) {
                    if (_numElement < num) {
                            std::cerr<<"Error. you give larger number"<<std::endl;
                            return ;
                    }
                    const double base = pow(static_cast<double>(num), 0.3333f);
                    node.clear();
                    while ( node.size() < num ) {
                            this->find(p, radius, node, false);
                            if (node.size() == 0) radius *= 2;
                            else  radius *= static_cast<double>(base / pow(node.size(), 0.3333));
                    }
                    node.sort(less_vec_length(p));
                    node.resize(num);
                    return;
            }
            /**
              * @brief Find a closest point.
              * @param[in] v A point.
              * @param[in] radius intial radius.
              * @return A point closest to v
              * @note If two or more closest points are found , it returns one of them.
              */
            T closest(const T& p, double radius = 0.001) {
                    std::list<T> node;
                    node.clear();
                    while (node.empty()) {
                            radius *= 2;
                            this->find(p, radius, node, true);
                    }
                    return *(node.begin());
            }
            /**
              * @brief Add new point to a tree
              * @param[in] d added point.
              */
            void add(const T& d) {
                    this->_parent.add(d, this->_numMaxElement);
                    this->_numElement += 1;
                    return;
            }

            /**
             * @return num. of element.
             */
            size_t size ( void ) const {
                    return this->_numElement;
            }

            /**
             * @return string of this class
             */
            std::string toString( void ) const {
                    std::stringstream ss;
                    ss<<"Kdtree : num_node "<<this->_numElement;
                    return ss.str();
            }
    };//class Kdtree
#endif// __MI_KDTREE_HPP__
