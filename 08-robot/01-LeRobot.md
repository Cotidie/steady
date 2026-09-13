# LeRobot

## Overview
- LeRobot은 허깅페이스 위에서 표준화된 데이터셋 형식으로 로봇 학습을 하기 위한 플랫폼
- pytorch와 같이, 로봇 학습 용도의 프레임워크
- 모델, 데이터셋, 도구를 Hugging Face Hub에서 받아 쓰고, 직접 만든 것도 공유 가능
- 저장소: https://github.com/huggingface/lerobot
- 사용 방식은 둘: 
  - CLI 스크립트(`lerobot-record`, `lerobot-train`, `lerobot-eval`)로 수집, 학습, 평가. 
  - Python API(`LeRobotDataset`)로 데이터 로드와 커스텀 학습
- CLI는 Python API 위에 만들어짐. 일상 작업은 CLI, 자체 모델이나 파이프라인 연동은 Python API

## 데이터셋 구조
`LeRobotDataset("lerobot/aloha_static_coffee")`로 로드한 객체의 속성. 저장 포맷은 주석 참조.

```python
dataset = LeRobotDataset("lerobot/aloha_static_coffee")

dataset.hf_dataset                    # Hugging Face Dataset, Parquet 저장. 프레임 하나가 한 행
  observation.images.cam_high         # VideoFrame: {'path': mp4 경로, 'timestamp': 비디오 내 시각 (float32)}
  observation.state                   # list[float32]: 로봇 팔 조인트 위치
  action                              # list[float32]: 로봇 팔 조인트 목표 위치
  episode_index                       # int64: 에피소드 번호
  frame_index                         # int64: 에피소드 내 프레임 번호, 에피소드마다 0부터
  timestamp                           # float32: 에피소드 내 시각
  next.done                           # bool: 에피소드의 마지막 프레임 여부
  index                               # int64: 데이터셋 전체 인덱스

dataset.episode_data_index            # 에피소드별 행 범위
  from                                # 1D int64: 에피소드 시작 프레임 인덱스
  to                                  # 1D int64: 에피소드 마지막 프레임 인덱스

dataset.stats                         # feature별 통계 (max, mean, min, std)
  observation.images.cam_high.max     # (채널, 1, 1) 텐서

dataset.info                          # 메타데이터, JSON/JSONL 저장
  codebase_version                    # str: 데이터셋 생성에 쓴 코드베이스 버전
  fps                                 # float: 프레임 속도
  video                               # bool: 비디오로 저장했는지 여부
  encoding                            # dict: 비디오 인코딩 ffmpeg 옵션

dataset.videos_dir                    # Path: mp4 또는 png 디렉토리
dataset.camera_keys                   # list[str]: 카메라 feature key 목록
```

기본 로컬 경로는 `~/.cache/huggingface/lerobot`, `root` 인자로 변경 가능.

출처: https://wikidocs.net/286289
