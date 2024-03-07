#include "git.h"

bool libmxfpp_git_IsPopulated() {
    return true;
}
bool libmxfpp_git_AnyUncommittedChanges() {
    return false;
}
const char* libmxfpp_git_AuthorName() {
    return "Philip de Nier";
}
const char* libmxfpp_git_AuthorEmail() {
    return "philipn@rd.bbc.co.uk";
}
const char* libmxfpp_git_CommitSHA1() {
    return "4d33dae366f9657d29c798ba1a40752084288ff9";
}
const char* libmxfpp_git_CommitDate() {
    return "2023-12-08 15:20:15 +0000";
}
const char* libmxfpp_git_CommitSubject() {
    return "Bump version to 1.2";
}
const char* libmxfpp_git_CommitBody() {
    return "";
}
const char* libmxfpp_git_Describe() {
    return "v1.2";
}
const char* libmxfpp_git_Branch() {
    return "ssimwave_v1.2_migrate_patches";
}
const char* libmxfpp_git_DescribeTag() {
    return "v1.2";
}