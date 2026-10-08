# ROS 2 패키지 구성 및 빌드 시스템 조사

## 1. 패키지를 구성하는 가장 중요한 필수 파일 2가지

ROS 2에서 ament_cmake 기반 패키지를 구성할 때 가장 중요한 파일은
`package.xml`과 `CMakeLists.txt`이다.

### ① package.xml
- 패키지의 이름, 버전, 설명, 작성자, 라이선스 등의 정보를 정의한다.
- 패키지를 빌드하거나 실행할 때 필요한 의존성을 명시한다.
- ROS 2의 빌드 도구인 colcon이 패키지의 의존 관계와 빌드 순서를 파악하는 데 사용한다.
- XML 형식으로 작성한다.

### ② CMakeLists.txt
- 소스코드를 컴파일하고 실행 파일이나 라이브러리를 생성하는 방법을 정의한다.
- 컴파일 옵션, 의존 라이브러리, 설치 경로 등을 설정한다.
- CMake 명령어를 사용하여 빌드 과정을 구성한다.
- ROS 2에서는 ament_cmake를 통해 ROS 전용 빌드 기능을 추가할 수 있다.

정리:
- package.xml → 패키지 정보 및 의존성 관리
- CMakeLists.txt → 소스코드 빌드 및 설치 방법 관리

※ Python 기반 ament_python 패키지는 CMakeLists.txt 대신
setup.py 등을 사용하는 구조이므로 구분해야 한다.


## 2. XML 파일 형식에 대하여 조사하시오.

### ① XML의 정의

XML(Extensible Markup Language)은 데이터를 구조적으로
표현하고 저장 및 교환하기 위해 사용하는 마크업 언어이다.

HTML이 주로 웹페이지의 표시를 목적으로 한다면,
XML은 데이터의 의미와 구조를 표현하는 데 목적이 있다.

### ② XML의 특징

1. 사용자가 직접 태그를 정의할 수 있다.
2. 시작 태그와 종료 태그를 사용하여 데이터를 구분한다.
3. 계층적인 트리 구조로 데이터를 표현한다.
4. 운영체제나 프로그래밍 언어와 관계없이 활용할 수 있다.
5. 대소문자를 구분하며, 태그의 중첩 구조가 올바르게 작성되어야 한다.
6. 태그의 속성을 이용하여 추가 정보를 표현할 수 있다.

### ③ XML 작성 예시

    <?xml version="1.0" encoding="UTF-8"?>
    <student>
        <name>Kim</name>
        <major>Embedded Software</major>
        <grade>3</grade>
    </student>

설명:
- <?xml ... ?> : XML 버전과 문자 인코딩 선언
- <student> : 최상위 요소(루트 요소)
- <name> : 학생 이름을 나타내는 요소
- <major> : 전공을 나타내는 요소
- <grade> : 학년을 나타내는 요소

### ④ ROS 2에서 XML을 사용하는 이유

ROS 2에서는 package.xml 파일을 통해 패키지의 정보를 관리한다.

예시:

    <package format="3">
        <name>my_package</name>
        <version>0.0.1</version>
        <description>ROS 2 example package</description>
        <maintainer email="user@example.com">user</maintainer>
        <license>Apache-2.0</license>

        <buildtool_depend>ament_cmake</buildtool_depend>
        <depend>rclcpp</depend>

        <export>
            <build_type>ament_cmake</build_type>
        </export>
    </package>

주요 요소:
- name : 패키지 이름
- version : 패키지 버전
- description : 패키지 설명
- maintainer : 패키지 관리자
- license : 라이선스 정보
- buildtool_depend : 빌드 도구 의존성
- depend : 패키지 의존성
- build_type : 사용할 빌드 시스템

이처럼 XML은 패키지의 정보를 일정한 구조로 관리하여
ROS 2의 빌드 도구가 패키지 정보를 해석할 수 있도록 한다.


## 3. ament_cmake와 CMake의 차이를 설명하시오.

### ① CMake

CMake는 C/C++ 등의 소스코드를 빌드하기 위한
크로스 플랫폼 빌드 시스템 생성 도구이다.

CMakeLists.txt 파일에 작성된 설정을 읽어
Makefile, Ninja 빌드 파일, Visual Studio 프로젝트 등
다양한 빌드 시스템을 생성할 수 있다.

주요 기능:
- 컴파일 및 빌드 과정 설정
- 실행 파일과 라이브러리 생성
- 외부 라이브러리 연결
- 컴파일 옵션 설정
- 운영체제별 빌드 환경 지원

일반적인 CMake 예시:

    cmake_minimum_required(VERSION 3.5)
    project(my_project)

    add_executable(my_program main.cpp)

설명:
- cmake_minimum_required() : 최소 CMake 버전 지정
- project() : 프로젝트 이름 설정
- add_executable() : 실행 파일 생성


### ② ament_cmake

ament_cmake는 ROS 2에서 사용하는 CMake 기반 빌드 시스템이다.

기존 CMake의 기능을 활용하면서
ROS 2 패키지 개발에 필요한 추가 기능을 제공한다.

주요 기능:
- ROS 2 패키지 빌드 지원
- ROS 2 패키지 간 의존성 연결 지원
- 패키지 설치 및 등록 지원
- 다른 ROS 2 패키지에서 사용할 수 있는 설정 정보 생성
- ROS 2 테스트 및 패키지 관리 기능 지원

ament_cmake 사용 예시:

    cmake_minimum_required(VERSION 3.5)
    project(my_package)

    find_package(ament_cmake REQUIRED)
    find_package(rclcpp REQUIRED)

    add_executable(my_node src/my_node.cpp)
    ament_target_dependencies(my_node rclcpp)

    install(TARGETS
        my_node
        DESTINATION lib/${PROJECT_NAME}
    )

    ament_package()

설명:
- find_package(ament_cmake REQUIRED)
  : ament_cmake 패키지를 검색한다.

- find_package(rclcpp REQUIRED)
  : ROS 2 C++ 클라이언트 라이브러리를 검색한다.

- ament_target_dependencies()
  : 실행 파일에 ROS 2 패키지 의존성을 연결한다.

- install()
  : 빌드한 실행 파일의 설치 경로를 지정한다.

- ament_package()
  : 패키지를 ament 인덱스에 등록하고
    다른 패키지에서 찾을 수 있도록 설정 정보를 생성한다.


### ③ CMake와 ament_cmake 비교

| 구분 | CMake | ament_cmake |
|------|-------|-------------|
| 목적 | 일반 소프트웨어 빌드 | ROS 2 패키지 빌드 |
| 적용 분야 | 다양한 C/C++ 프로젝트 | 주로 ROS 2 C/C++ 프로젝트 |
| 기반 기술 | 독립적인 빌드 도구 | CMake 기반 확장 |
| 설정 파일 | CMakeLists.txt | CMakeLists.txt |
| 의존성 관리 | find_package() 등 | find_package(), ament 관련 기능 |
| 패키지 등록 | 일반 CMake 패키지 설정 | ament_package() |
| ROS 2 연동 | 별도 설정 필요 | ROS 2 전용 기능 제공 |

### ④ 핵심 차이

CMake는 일반적인 C/C++ 프로젝트의 빌드 과정을 관리하는 도구이다.

반면 ament_cmake는 CMake를 기반으로 ROS 2 패키지의
의존성 처리, 설치, 패키지 등록 등의 기능을 추가한 빌드 시스템이다.

따라서 ament_cmake는 CMake와 완전히 별개의 도구가 아니라,
CMake를 확장하여 ROS 2 개발 환경에 적합하게 만든 시스템이다.


## 4. 결론

1. ROS 2의 ament_cmake 패키지를 구성하는 핵심 파일은
   package.xml과 CMakeLists.txt이다.

2. XML은 데이터를 계층적 구조로 표현하는 마크업 언어이며,
   ROS 2에서는 package.xml을 통해 패키지 정보를 관리한다.

3. CMake는 일반적인 소프트웨어 빌드 도구이고,
   ament_cmake는 CMake를 기반으로 ROS 2 패키지 관리와
   빌드 기능을 확장한 시스템이다.


## 5. 참고 자료

1. ROS 2 Foxy - ament_cmake Documentation
   https://docs.ros.org/en/foxy/How-To-Guides/Ament-CMake-Documentation.html

2. CMake 공식 문서
   https://cmake.org/cmake/help/latest/

3. ROS 2 Foxy - Build System
   https://docs.ros.org/en/foxy/Concepts/About-Build-System.html
