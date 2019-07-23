#!/bin/bash -e

boost_version="${1}"
boost_file=$(echo ${boost_version} | tr '.' '_')
toolset="${2}"
cxxflags="${3}"
linkflags="${4}"

if [ "${cxxflags}" != "" ] ; then arg_cxxflags="cxxflags=${cxxflags}" ; fi
if [ "${linkflags}" != "" ] ; then arg_linkflags="linkflags=${linkflags}" ; fi

prefix=/opt/local

curl -o /tmp/boost.tar.bz2 -L https://dl.bintray.com/boostorg/release/${boost_version}/source/boost_${boost_file}.tar.bz2
cd /tmp
tar -xf boost.tar.bz2
rm -f boost.tar.bz2
cd boost_${boost_file}
./bootstrap.sh --with-toolset=${toolset} --prefix=${prefix} --with-libraries=system
./b2 -j3 --prefix=${prefix} \
	toolset=${toolset} \
	${arg_cxxflags} \
	${arg_linkflags} \
	threading=multi \
	variant=release \
	optimization=space \
	install
cd /opt
rm -fr /tmp/boost_${boost_file}
