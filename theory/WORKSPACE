workspace(name = "com_github_gflags_example")

git_repository(
    name   = "com_github_gflags_gflags",
    #tag    = "v2.2.0",
    commit = "30dbc81fb5ffdc98ea9b14b1918bfe4e8779b26e", # v2.2.0 + fix of include path
    remote = "https://github.com/gflags/gflags.git"
)

bind(
    name   = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

bind(
    name   = "gflags_nothreads",
    actual = "@com_github_gflags_gflags//:gflags_nothreads",
)
