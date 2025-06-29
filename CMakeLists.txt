cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(1DHeatConduction CXX)

# FetchContent を含める (nlohmann/json用)
include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3 # 使用したいバージョンタグを指定
)
FetchContent_MakeAvailable(nlohmann_json)

# srcディレクトリ内のすべての .cpp ファイルを取得
# GLOB_RECURSE を使うとサブディレクトリも検索しますが、現在の構造ではGLOBで十分です
file(GLOB SOURCE_FILES "src/*.cpp")

# add_executable に取得したソースファイルを渡す
# ヘッダファイルは通常、target_include_directories でコンパイラにパスを伝えるため、
# add_executable に含める必要はありません（コンパイル対象は.cppファイルです）
add_executable(heat_conduction ${SOURCE_FILES})
target_include_directories(heat_conduction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# nlohmann/json を実行ファイルにリンクする
target_link_libraries(heat_conduction PRIVATE nlohmann_json::nlohmann_json)


# 共有ライブラリビルドに変更
add_library(heat_conduction_solver SHARED ${SOURCE_FILES})

target_include_directories(heat_conduction_solver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(heat_conduction_solver PRIVATE nlohmann_json::nlohmann_json)