

# 실습과제 1

## 1. CMake와 GNU Make의 차이점

CMake와 GNU Make는 모두 프로그램을 빌드하는 과정에서 사용되지만 역할이 다르다.

GNU Make는 `Makefile`에 작성된 규칙을 읽고 실제로 소스 코드를 컴파일하고 링크하는 빌드 도구이다.  
즉, 어떤 소스 파일을 어떤 컴파일러와 옵션으로 컴파일할 것인지 `Makefile`에 정의되어 있으며, `make` 명령을 실행하면 해당 규칙에 따라 빌드가 수행된다.

반면 CMake는 직접 컴파일을 수행하는 도구라기보다 빌드 시스템을 생성하는 도구이다.  
CMake는 `CMakeLists.txt`에 작성된 프로젝트 설정을 읽고, 사용 중인 개발 환경에 맞는 `Makefile`, Ninja 빌드 파일, Visual Studio 프로젝트 파일 등을 생성한다.

따라서 GNU Make와 CMake의 관계는 다음과 같이 정리할 수 있다.

```text
CMakeLists.txt
      ↓
    CMake
      ↓
   Makefile
      ↓
     make
      ↓
컴파일 및 링크
      ↓
   실행 파일
```

즉, CMake는 빌드에 필요한 파일을 생성하는 역할을 하고 GNU Make는 생성된 `Makefile`을 이용하여 실제 빌드를 수행한다.

---

## 2. CMakeLists.txt의 역할

`CMakeLists.txt`는 CMake가 프로젝트를 어떻게 구성하고 빌드할 것인지 정의하는 설정 파일이다.

예를 들어 다음과 같이 작성할 수 있다.

```cmake
cmake_minimum_required(VERSION 3.10)

project(Hello)

add_executable(Hello main.cpp)
```

각 명령의 역할은 다음과 같다.

- `cmake_minimum_required(VERSION 3.10)`
  - 프로젝트를 빌드하기 위해 필요한 최소 CMake 버전을 지정한다.

- `project(Hello)`
  - 프로젝트의 이름을 `Hello`로 지정한다.

- `add_executable(Hello main.cpp)`
  - `main.cpp` 소스 파일을 이용하여 `Hello`라는 실행 파일을 생성하도록 설정한다.

`CMakeLists.txt`에는 이외에도 다음과 같은 정보를 작성할 수 있다.

- 프로젝트 이름
- 소스 파일 목록
- 실행 파일 및 라이브러리 이름
- Include 디렉토리
- 외부 라이브러리
- 컴파일 옵션
- 링크 옵션
- 빌드 조건

따라서 `CMakeLists.txt`는 CMake 프로젝트의 전체적인 빌드 방법을 정의하는 핵심 설정 파일이라고 할 수 있다.

---

## 3. CMakeCache.txt의 역할

`CMakeCache.txt`는 CMake의 Configure 단계에서 확인하거나 결정된 설정값을 저장하는 캐시 파일이다.

예를 들어 다음 명령을 실행하면:

```bash
cmake -S src -B build
```

`build` 디렉토리 내부에 `CMakeCache.txt`가 생성된다.

```text
hello/
├── src/
│   ├── CMakeLists.txt
│   └── main.cpp
└── build/
    ├── CMakeCache.txt
    ├── CMakeFiles/
    ├── Makefile
    └── cmake_install.cmake
```

`CMakeCache.txt`에는 다음과 같은 정보가 저장된다.

- C/C++ 컴파일러의 위치
- 프로젝트의 소스 디렉토리
- Build 디렉토리
- CMake 관련 경로
- 라이브러리 검색 결과
- 사용자가 설정한 빌드 옵션
- Build Type 등의 설정값

CMake가 다시 실행될 때는 이전에 저장된 `CMakeCache.txt`를 참고하여 동일한 설정을 재사용할 수 있다.

따라서 `CMakeCache.txt`는 Configure 단계에서 결정된 환경 및 빌드 설정 정보를 저장하여 이후 CMake 실행 시 재사용하는 역할을 한다.

---

## 4. CMake의 각 단계별 결과물

CMake의 일반적인 빌드 과정은 다음과 같이 구분할 수 있다.

```text
Configure
    ↓
Generate
    ↓
Build
```

### 4.1 Configure 단계

Configure 단계에서는 CMake가 `CMakeLists.txt`를 읽고 프로젝트의 빌드 환경을 확인한다.

예를 들어 다음 명령을 실행한다.

```bash
cmake -S src -B build
```

이 과정에서 CMake는 다음과 같은 내용을 확인한다.

- 사용할 C/C++ 컴파일러
- 컴파일러의 종류와 버전
- 소스 파일의 존재 여부
- 라이브러리 및 Include 경로
- 사용자가 지정한 빌드 옵션
- 운영체제 및 시스템 환경

Configure 단계의 대표적인 결과물은 다음과 같다.

```text
CMakeCache.txt
CMakeFiles/
```

`CMakeCache.txt`에는 확인된 환경과 설정값이 저장된다.

`CMakeFiles/` 디렉토리에는 컴파일러 정보, 시스템 정보, 프로젝트 설정 등 CMake가 내부적으로 사용하는 여러 파일이 생성된다.

실행 화면에서는 다음과 같은 메시지를 확인할 수 있다.

```text
-- The CXX compiler identification is GNU ...
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
```

---

### 4.2 Generate 단계

Configure 단계가 정상적으로 완료되면 CMake는 Generate 단계를 수행한다.

Generate 단계에서는 Configure 단계에서 결정된 정보를 이용하여 실제 빌드 도구가 사용할 빌드 파일을 생성한다.

GNU Make를 사용하는 환경에서는 대표적으로 다음 파일이 생성된다.

```text
Makefile
CMakeFiles/Makefile2
CMakeFiles/Hello.dir/build.make
```

가장 중요한 결과물은 `Makefile`이다.

```text
CMakeLists.txt
      ↓
Configure
      ↓
Generate
      ↓
Makefile
```

실행 화면에서는 다음과 같은 메시지를 확인할 수 있다.

```text
-- Generating done
-- Build files have been written to: /home/linux/hello/build
```

즉, Generate 단계의 결과는 실제 빌드 도구가 사용할 수 있는 빌드 파일을 생성하는 것이다.

---

### 4.3 Build 단계

Build 단계에서는 Generate 단계에서 만들어진 빌드 파일을 이용하여 실제 소스 코드의 컴파일과 링크를 수행한다.

CMake를 이용하는 경우 다음과 같이 실행할 수 있다.

```bash
cmake --build build
```

GNU Make를 직접 사용하는 경우 `build` 디렉토리로 이동한 후 다음과 같이 실행할 수 있다.

```bash
make
```

Build 단계에서는 먼저 소스 파일이 Object 파일로 컴파일된다.

```text
main.cpp
   ↓
컴파일
   ↓
main.cpp.o
```

그다음 Object 파일을 링크하여 최종 실행 파일을 생성한다.

```text
main.cpp.o
   ↓
링크
   ↓
Hello
```

따라서 Build 단계의 주요 결과물은 다음과 같다.

- `main.cpp.o`
  - 소스 코드가 컴파일된 Object 파일

- `Hello`
  - Object 파일을 링크하여 생성된 최종 실행 파일

전체 CMake 빌드 과정을 정리하면 다음과 같다.

```text
CMakeLists.txt
      ↓
Configure
      ↓
CMakeCache.txt
CMakeFiles/
      ↓
Generate
      ↓
Makefile
      ↓
Build
      ↓
main.cpp.o
      ↓
Hello
```

---

## 5. `cmake --build build` 대신 `make` 명령어를 이용한 빌드


<img width="1104" height="583" alt="image" src="https://github.com/user-attachments/assets/0005b8e4-9407-43fc-89ae-78183398d1b8" />




# 실습과제 2
<img width="703" height="324" alt="image" src="https://github.com/user-attachments/assets/2288e8ed-3e23-40cc-9753-a4f177b302a9" />
