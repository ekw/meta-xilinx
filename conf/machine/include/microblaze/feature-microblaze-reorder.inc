TUNEVALID[reorder] = "Enable Microblaze Reorder Instructions."
MBCCARGSREORDER = "${@bb.utils.contains("TUNE_FEATURES", "reorder", "-mxl-reorder", "-mno-xl-reorder" ,d)}"
MBPKGREORDER = "${@bb.utils.contains("TUNE_FEATURES", "reorder", "-re", "" ,d)}"

# Not avaliable on CPUs older that v8.30
TUNECONFLICTS[reorder] += "v8.20 v8.10 v8.00 v7.30"
