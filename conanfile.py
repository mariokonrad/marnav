from conans import ConanFile, CMake, tools
import os, re


class Package(ConanFile):
    license = "BSD"
    description = "This is a C++ library for MARitime NAVigation purposes."
    url = "https://github.com/mariokonrad/marnav"

    settings = "os", "arch", "compiler", "build_type"

    options = {"shared": [True, False]}
    default_options = {"shared": False}

    exports_sources = [
        'LICENSE',
        'CMakeLists.txt',
        'Packaging.cmake',
        'README.md',
        'doxygen.conf.in',
        'doc/*',
        'include/*',
        'src/*',
        'cmake/*'
        #'test/*'
        #'extern/*'
        ]

    __cmake = None

    def __cmake_info(self):
        cmakelists = tools.load(os.path.join(self.recipe_folder, 'CMakeLists.txt'))
        result = re.search(r'project\s*\(\s*([a-zA-Z0-9-_]+)\s+\bVERSION\b\s+(\d+\.\d+\.\d+)(.|\s)*\)',
                           cmakelists)
        return result.group(1), result.group(2)

    def __setup_cmake(self):
        if not self.__cmake:
            self.__cmake = CMake(self)
            self.__cmake.definitions['ENABLE_PROFILING'] = "FALSE"
            self.__cmake.definitions['ENABLE_BENCHMARK'] = "FALSE"
            self.__cmake.definitions['ENABLE_SANITIZER'] = "FALSE"
            self.__cmake.definitions['ENABLE_EXAMPLES'] = "FALSE"
            self.__cmake.definitions['ENABLE_TESTS'] = "FALSE"
            self.__cmake.definitions['ENABLE_TOOLS'] = "FALSE"
            self.__cmake.definitions['ENABLE_IWYU'] = "FALSE"
        return self.__cmake

    def set_name(self):
        name, version = self.__cmake_info()
        self.name = name

    def set_version(self):
        name, version = self.__cmake_info()
        self.version = version

    def build(self):
        cmake = self.__setup_cmake()
        cmake.configure()
        cmake.build()
        #cmake.test(target="unittest")

    def package(self):
        cmake = self.__setup_cmake()
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = [self.name]

