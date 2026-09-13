## 링크
[https://leetcode.com/problems/search-suggestions-system/](https://leetcode.com/problems/search-suggestions-system/)

## 관련 개념
* Trie
* 백트래킹

## 풀이
1. 주어진 단어들을 저장할 Trie를 선언합니다.
  - insert(word): 단어 하나를 Trie에 집어 넣습니다.
  - search(prefix, num): 접두사로 단어를 검색합니다. 이때 num개수만큼만 찾습니다.
2. 그동안 찾은 단어들을 저장할 Trie를 선언합니다. (History)
  - 한 글자씩 검색할 때마다, 그 이전 prefix는 바뀌지 않습니다.
3. 한 글자씩 순회하며 Trie를 검색합니다.
  - 검색 이전에 먼저 History에 존재하는지 검사합니다.
4. History에서 부족한 개수만큼만 추가로 찾습니다.

## 비고/남길말
 Cpp에서 포인터를 잘 사용해야 함을 다시 한번 느낍니다. 포인터를 쓰지 않으면 스코프를 벗어날 때 자동해제되어 쓰레기 값을 갖게 되었습니다.
