# Setup tune features for each version of the MicroBlaze
TUNEVALID[v9.0] = "MicroBlaze version 9.0"
TUNEVALID[v8.50] = "MicroBlaze version 8.50"
TUNEVALID[v8.40] = "MicroBlaze version 8.40"
TUNEVALID[v8.30] = "MicroBlaze version 8.30"
TUNEVALID[v8.20] = "MicroBlaze version 8.20"
TUNEVALID[v8.10] = "MicroBlaze version 8.10"
TUNEVALID[v8.00] = "MicroBlaze version 8.00"
TUNEVALID[v7.30] = "MicroBlaze version 7.30"

# Setup mapping values for each feature to hardware version string
MBCPUVERSION[v9.0] = "9.0"
MBCPUVERSION[v8.50] = "8.50.a"
MBCPUVERSION[v8.40] = "8.40.a"
MBCPUVERSION[v8.30] = "8.30.a"
MBCPUVERSION[v8.20] = "8.20.a"
MBCPUVERSION[v8.10] = "8.10.a"
MBCPUVERSION[v8.00] = "8.00.a"
MBCPUVERSION[v7.30] = "7.30.a"

# Setup a 'feature set' conflict list which ensures only one version is selected
# when defining the TUNE_FEATURES_tune-<>  in local.conf file.
TUNECONFLICTS[v9.0]  += "v7.30 v8.00 v8.10 v8.20 v8.30 v8.40 v8.50"
TUNECONFLICTS[v8.50] += "v7.30 v8.00 v8.10 v8.20 v8.30 v8.40 v9.0"
TUNECONFLICTS[v8.40] += "v7.30 v8.00 v8.10 v8.20 v8.30 v8.50 v9.0"
TUNECONFLICTS[v8.30] += "v7.30 v8.00 v8.10 v8.20 v8.40 v8.50 v9.0"
TUNECONFLICTS[v8.20] += "v7.30 v8.00 v8.10 v8.30 v8.40 v8.50 v9.0"
TUNECONFLICTS[v8.10] += "v7.30 v8.00 v8.20 v8.30 v8.40 v8.50 v9.0"
TUNECONFLICTS[v8.00] += "v7.30 v8.10 v8.20 v8.30 v8.40 v8.50 v9.0"
TUNECONFLICTS[v7.30] += "v8.00 v8.10 v8.20 v8.30 v8.40 v8.50 v9.0"

# Helper functions
def mb_tune_format(version):
    if version:
        return version.rsplit(".", 1)[0].strip("v")
    return ""

def mb_get_version(d):
    tune_features = (d.getVar("TUNE_FEATURES", True) or "").split()
    versions = d.getVarFlags("MBCPUVERSION")
    for i in versions.iteritems():
        if i[0] in tune_features:
            return i[1]
    return ""

MBCPUVERSION = "${@mb_get_version(d)}"
MBCCARGSVERSION = "-mcpu=v${MBCPUVERSION}"
MBPKGVERSION = "-v${@mb_tune_format(d.getVar('MBCPUVERSION', True))}"

# Perform some additional sanity checking
python __anonymous () {
    tune_features = d.getVar('TUNE_FEATURES', True)
    tuneslist = tune_features.split()

    # GCC will fail on v8.30 if reorder and pattern-compare are not both in
    # ccflags.
    if 'v8.30' in tuneslist:
        if 'reorder' in tuneslist and 'pattern-compare' not in tuneslist:
            d.setVar("TUNE_FEATURES", "%s pattern-compare" % tune_features)
}
