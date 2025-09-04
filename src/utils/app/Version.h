// version.h
#ifndef VERSION_H
#define VERSION_H

#include <QString>

namespace Version {
// Constantes de versión
const int MAJOR = APP_VERSION_MAJOR;
const int MINOR = APP_VERSION_MINOR;
const int PATCH = APP_VERSION_PATCH;
const QString BUILD = APP_VERSION_SUFFIX;

// Obtener la versión completa como string
inline QString getVersion() {
    return QString("%1.%2.%3-%4")
    .arg(MAJOR)
        .arg(MINOR)
        .arg(PATCH)
        .arg(BUILD);
}

// Estructura para representar una versión
struct VersionInfo {
    int major;
    int minor;
    int patch;
    QString build;

    bool operator<(const VersionInfo& other) const {
        if (major != other.major) return major < other.major;
        if (minor != other.minor) return minor < other.minor;
        return patch < other.patch;
    }

    bool operator==(const VersionInfo& other) const {
        return major == other.major &&
               minor == other.minor &&
               patch == other.patch &&
               build == other.build;
    }
};

// Funciones de utilidad
inline VersionInfo getCurrentVersion() {
    return {MAJOR, MINOR, PATCH, BUILD};
}

inline bool checkCompatibility(const VersionInfo& minimum) {
    VersionInfo current = getCurrentVersion();
    return !(current < minimum);
}

// Para verificar actualizaciones
inline bool isUpdateAvailable(const VersionInfo& latestVersion) {
    return getCurrentVersion() < latestVersion;
}

// Para mostrar información detallada
inline QString getVersionDetails() {
    return QString(
               "Versión: %1\n"
               "Compilado: %2\n"
               "Qt: %3")
        .arg(getVersion())
        .arg(__DATE__)
        .arg(QT_VERSION_STR);
}
}

#endif // VERSION_H
