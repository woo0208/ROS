# WSL2의 기능

## 1. WSL2란?

**WSL2(Windows Subsystem for Linux 2)**는 Windows에서 **Linux 환경을 직접 실행할 수 있도록 해주는 기능**입니다.

쉽게 말하면, Windows를 사용하면서 Ubuntu와 같은 Linux 배포판을 별도의 PC나 듀얼부팅 없이 사용할 수 있게 해줍니다.

WSL2는 기존 WSL1의 후속 버전으로, **Linux 호환성과 성능을 크게 향상**시킨 것이 특징입니다.

---

## 2. WSL2의 주요 기능

### 2.1 Linux 환경 실행

Windows에서 Ubuntu, Debian, Kali Linux 등의 Linux 배포판을 실행할 수 있습니다.

Linux의 다양한 명령어와 도구를 사용할 수 있습니다.

예를 들어 다음과 같은 명령어를 사용할 수 있습니다.

- bash
- grep
- awk
- sed
- ssh

### 2.2 실제 Linux 커널 사용

WSL1은 Windows에서 Linux 시스템 호출을 변환하는 방식이었지만, **WSL2는 실제 Linux 커널을 사용**합니다.

따라서 Linux 애플리케이션과의 호환성이 WSL1보다 크게 향상되었습니다.

특히 다음과 같은 도구를 사용하는 데 유리합니다.

- Docker
- Linux 서버 프로그램
- Linux 기반 개발 도구
- 컨테이너 환경

### 2.3 Windows와 Linux 파일 시스템 연동

WSL2에서는 Windows와 Linux의 파일 시스템을 서로 접근할 수 있습니다.

예를 들어 Windows의 다음 경로가 있다고 가정하면:

C:\Users\User\Documents

WSL2에서는 다음과 같이 접근할 수 있습니다.

/mnt/c/Users/User/Documents

반대로 Windows에서도 WSL의 Linux 파일 시스템에 접근할 수 있습니다.

### 2.4 Windows 프로그램과 Linux 프로그램 연동

WSL2에서는 Linux 프로그램과 Windows 프로그램을 함께 사용할 수 있습니다.

예를 들어 WSL에서 Windows 프로그램을 실행하거나, Windows의 PowerShell에서 WSL의 Linux 명령을 실행할 수 있습니다.

이를 통해 Windows의 GUI 환경과 Linux의 CLI 환경을 함께 사용할 수 있습니다.

### 2.5 개발 환경 구축

WSL2는 개발 환경으로 많이 사용됩니다.

다음과 같은 개발 도구를 Linux 환경에서 사용할 수 있습니다.

- Python
- Node.js
- Java
- C/C++
- Go
- Rust
- Git
- SSH

특히 실제 서버가 Linux 환경인 경우, Windows PC에서도 **서버와 유사한 Linux 개발 환경**을 구축할 수 있다는 장점이 있습니다.

### 2.6 Docker 및 컨테이너 사용

WSL2는 Docker와의 통합을 지원하기 때문에 **Docker 기반 개발 환경**을 구축하는 데 적합합니다.

예를 들어 다음과 같은 환경을 구성할 수 있습니다.

Windows
  └── WSL2
       └── Ubuntu
            ├── Docker
            ├── Nginx
            ├── MySQL
            ├── Redis
            └── 개발 프로그램

### 2.7 Linux GUI 애플리케이션 실행

최신 WSL2에서는 **WSLg**를 통해 Linux GUI 애플리케이션도 Windows에서 실행할 수 있습니다.

따라서 Linux용 GUI 프로그램을 Windows 데스크톱 환경에서 사용하는 것도 가능합니다.

---

## 3. WSL1과 WSL2의 차이

| 구분 | WSL1 | WSL2 |
|---|---|---|
| Linux 커널 | Windows에서 시스템 호출 변환 | **실제 Linux 커널 사용** |
| Linux 호환성 | 상대적으로 제한적 | **높은 호환성** |
| Linux 파일 시스템 | 제한적 | **Linux 파일 시스템 지원** |
| Docker | 제한적 | **적합** |
| 가상화 기술 | 사용하지 않음 | **경량 가상화 기술 사용** |
| 현재 활용도 | 특정 환경 | **대부분의 일반적인 용도** |

---

## 4. WSL2는 가상머신인가?

WSL2는 **가상화 기술을 사용합니다.**

다만 VirtualBox나 VMware처럼 사용자가 직접 가상 머신을 생성하고 관리하는 방식과는 다릅니다.

WSL2는 Windows가 관리하는 **경량 가상 머신 환경**에서 Linux 커널을 실행합니다.

따라서 사용자는 복잡한 VM 설정 없이 다음과 같이 Linux 환경을 실행할 수 있습니다.

wsl

---

## 5. WSL2를 사용하면 좋은 경우

WSL2는 특히 다음과 같은 상황에서 유용합니다.

- Windows에서 Linux 서버 프로그램을 개발하는 경우
- Docker를 사용하는 경우
- Python, Node.js 등의 개발 환경이 필요한 경우
- Linux 기반 오픈소스 프로젝트를 빌드하는 경우
- Linux 서버와 비슷한 개발 환경이 필요한 경우
- Windows와 Linux 환경을 동시에 사용해야 하는 경우

---

## 6. WSL2의 전체적인 구조

WSL2의 구조를 간단하게 표현하면 다음과 같습니다.

Windows
  │
  └── WSL2
       │
       └── Ubuntu
            ├── Linux Kernel
            ├── Bash
            ├── Python
            ├── Node.js
            └── Docker

---

## 7. 요약

WSL2는 **Windows에서 Linux 환경을 편리하게 사용할 수 있도록 해주는 기능**입니다.

핵심적인 특징은 다음과 같습니다.

1. **실제 Linux 커널을 사용한다.**
2. **Windows에서 Ubuntu 등의 Linux 배포판을 실행할 수 있다.**
3. **Windows와 Linux의 파일 시스템을 연동할 수 있다.**
4. **Windows와 Linux 프로그램을 함께 사용할 수 있다.**
5. **Docker 및 컨테이너 환경에 적합하다.**
6. **개발 환경을 Linux 서버와 비슷하게 구성할 수 있다.**
7. **WSLg를 통해 Linux GUI 프로그램도 실행할 수 있다.**

### 한 문장으로 정리

> **WSL2는 Windows의 편리한 사용 환경을 유지하면서 실제 Linux 커널 기반의 Linux 개발 환경을 함께 사용할 수 있도록 해주는 기능이다.**
