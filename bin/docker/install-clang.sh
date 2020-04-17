#!/bin/bash -e

compiler_version="${1}"

base_url="http://releases.llvm.org"
github_base_url="https://github.com/llvm/llvm-project/releases/download"

function get_url()
{
	compiler_version="${1}"
	case "${compiler_version}" in
		"3.7.1"|"3.8.0"|"3.8.1"|"3.9.0"|"3.9.1"|"4.0.0"|"4.0.1"|"5.0.0"|"5.0.1"|"6.0.0")
			echo "${base_url}/${compiler_version}/clang+llvm-${compiler_version}-x86_64-linux-gnu-debian8.tar.xz"
			;;
		"3.6.1"|"3.6.2"|"3.7.0"|"5.0.2"|"6.0.1"|"7.0.0"|"7.0.1"|"7.1.0"|"8.0.0"|"9.0.0")
			echo "${base_url}/${compiler_version}/clang+llvm-${compiler_version}-x86_64-linux-gnu-ubuntu-14.04.tar.xz"
			;;
		"10.0.0")
			echo "${github_base_url}/llvmorg-${compiler_version}/clang+llvm-${compiler_version}-x86_64-linux-gnu-ubuntu-18.04.tar.xz"
			;;
		*)
			exit 1
			;;
	esac
}

curl --output /tmp/clang.tar.xz -L $(get_url "${compiler_version}")
tar -xaf /tmp/clang.tar.xz --strip-components=1 -C /usr
rm /tmp/clang.tar.xz

which clang   && clang   --version
which clang++ && clang++ --version
