# LeRobot

## Overview
- LeRobot은 허깅페이스 위에서 표준화된 데이터셋 형식으로 로봇 학습을 하기 위한 플랫폼
- pytorch와 같이, 로봇 학습 용도의 프레임워크
- 모델, 데이터셋, 도구를 Hugging Face Hub에서 받아 쓰고, 직접 만든 것도 공유 가능
- 저장소: https://github.com/huggingface/lerobot

## 데이터셋 구조
`LeRobotDataset("lerobot/aloha_static_coffee")` 기준.

| 구성 요소 | 타입 | 내용 |
|---|---|---|
| `hf_dataset` | HF Dataset (Parquet) | 프레임 단위 데이터. 아래 필드 참조 |
| `episode_data_index` | dict of 1D int64 | `from`: 에피소드 시작 프레임 인덱스, `to`: 마지막 프레임 인덱스 |
| `stats` | dict | feature별 max, mean, min, std. 예: `observation.images.cam_high.max` 는 (채널, 1, 1) 텐서 |
| `info` | dict | `codebase_version`(str), `fps`(float), `video`(bool), `encoding`(ffmpeg 옵션 dict) |
| `videos_dir` | Path | mp4 또는 png가 저장된 디렉토리 |
| `camera_keys` | list[str] | 카메라 feature에 접근하는 key 목록 |

### hf_dataset 필드

| 필드 | 타입 | 내용 |
|---|---|---|
| `observation.images.cam_high` | VideoFrame | `path`: mp4 경로, `timestamp`: 비디오 내 시각(float32) |
| `observation.state` | list[float32] | 로봇 팔 조인트 위치 |
| `action` | list[float32] | 로봇 팔 조인트 목표 위치 |
| `episode_index` | int64 | 에피소드 번호 |
| `frame_index` | int64 | 에피소드 내 프레임 번호 (에피소드마다 0부터) |
| `timestamp` | float32 | 에피소드 내 시각 |
| `next.done` | bool | 에피소드의 마지막 프레임 여부 |
| `index` | int64 | 데이터셋 전체 인덱스 |

### 저장 포맷

| 대상 | 포맷 |
|---|---|
| `hf_dataset` | Parquet (HF datasets) |
| 비디오 | mp4 |
| 메타데이터 | JSON / JSONL |

기본 로컬 경로는 `~/.cache/huggingface/lerobot`, `root` 인자로 변경 가능.

출처: https://wikidocs.net/286289
