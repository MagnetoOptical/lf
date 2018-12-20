package lf

import "fmt"

// LF version and software implementation name
const (
	VersionMajor    = 0
	VersionMinor    = 0
	VersionRevision = 1
	VersionBuild    = 0

	SoftwareName = "ZeroTier LF (\"Project Azathoth\")"
)

var versionStr = fmt.Sprintf("%d.%d.%d.%d", VersionMajor, VersionMinor, VersionRevision, VersionBuild)