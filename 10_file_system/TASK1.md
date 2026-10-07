
# 빌드 시스템과 패키지 생성 및 빌드

## 1. 빌드 시스템과 빌드 툴의 차이를 설명하라.

### 빌드 시스템(Build System)

빌드 시스템은 소스 코드를 실행 가능한 프로그램이나 라이브러리로 변환하는 **전체 빌드 과정을 관리하는 체계**이다.

빌드에 필요한 파일의 의존성, 컴파일 순서, 컴파일 옵션, 링크 과정 등을 관리한다.

대표적인 빌드 시스템으로는 CMake, Make, Ninja 등이 있다.

### 빌드 툴(Build Tool)

빌드 툴은 빌드 시스템에서 정의된 규칙에 따라 실제로 컴파일과 링크 작업을 수행하는 도구이다.

예를 들어 CMake를 이용해 빌드 설정을 생성하고, Make 또는 Ninja를 이용해 실제 빌드를 수행할 수 있다.

즉,

- **빌드 시스템**: 전체 빌드 과정과 규칙을 관리
- **빌드 툴**: 정의된 규칙에 따라 실제 빌드를 수행

---

## 2. 패키지 생성 명령어를 실행하는 위치는 어디이고 그곳으로 이동하는 명령어를 쓰시오.

ROS 2에서 새로운 패키지를 생성할 때는 일반적으로 ROS 2 작업공간의 `src` 디렉토리에서 실행한다.

작업공간의 이름이 `ros2_ws`라면 다음 명령어로 이동한다.

```bash
cd ~/ros2_ws/src
```

현재 위치는 다음 명령어로 확인할 수 있다.

```bash
pwd
```

---

## 3. 패키지 생성 명령어의 사용법을 설명하라.

ROS 2에서는 `ros2 pkg create` 명령어를 사용하여 새로운 패키지를 생성한다.

기본 형식은 다음과 같다.

```bash
ros2 pkg create <패키지이름>
```

C/C++ 기반의 패키지를 생성할 경우 `ament_cmake` 빌드 타입을 지정할 수 있다.

```bash
ros2 pkg create --build-type ament_cmake <패키지이름>
```

예를 들어 `my_package`라는 이름의 패키지를 생성하려면 다음과 같이 실행한다.

```bash
ros2 pkg create --build-type ament_cmake my_package
```

Python 기반의 패키지를 생성하는 경우에는 다음과 같이 실행한다.

```bash
ros2 pkg create --build-type ament_python my_package
```

패키지를 생성하면서 필요한 의존성을 함께 지정할 수도 있다.

```bash
ros2 pkg create --build-type ament_cmake --dependencies rclcpp std_msgs my_package
```

이 명령을 실행하면 패키지에 필요한 기본 디렉토리와 `CMakeLists.txt`, `package.xml` 등의 파일이 생성된다.

---

## 4. 패키지 빌드 명령어를 실행하는 위치는 어디이고 그곳으로 이동하는 명령어를 쓰시오.

ROS 2 패키지를 빌드할 때는 개별 패키지 디렉토리가 아니라 ROS 2 작업공간의 **최상위 디렉토리**에서 실행한다.

작업공간의 이름이 `ros2_ws`라면 다음 명령어로 이동한다.

```bash
cd ~/ros2_ws
```

일반적인 작업공간의 구조는 다음과 같다.

```text
ros2_ws/
├── build/
├── install/
├── log/
└── src/
```

`colcon build` 명령어는 `ros2_ws` 위치에서 실행한다.

---

## 5. 패키지 빌드 명령어의 사용법을 설명하라.

ROS 2에서는 일반적으로 `colcon`을 이용하여 패키지를 빌드한다.

작업공간에 존재하는 모든 패키지를 빌드하려면 다음 명령어를 사용한다.

```bash
colcon build
```

특정 패키지만 빌드하려면 `--packages-select` 옵션을 사용한다.

```bash
colcon build --packages-select <패키지이름>
```

예를 들어 `my_package` 패키지만 빌드하려면 다음과 같이 실행한다.

```bash
colcon build --packages-select my_package
```

빌드가 정상적으로 완료되면 작업공간에 다음 디렉토리가 생성된다.

```text
build/
install/
log/
```

빌드가 완료된 후 생성된 패키지를 사용하기 위해서는 다음 명령어를 실행하여 환경 설정을 적용한다.

```bash
source install/setup.bash
```

전체적인 패키지 생성 및 빌드 과정은 다음과 같다.

```bash
cd ~/ros2_ws/src

ros2 pkg create --build-type ament_cmake my_package

cd ~/ros2_ws

colcon build

source install/setup.bash
```
