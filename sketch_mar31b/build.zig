const exe = b.addExecutable("firmware", "src/main.zig");
exe.addCSourceFile("src/servo_wrapper.cpp", &[_][]const u8{"-std=c++11"});
exe.linkLibCpp(); // C++ 표준 라이브러리 링크
