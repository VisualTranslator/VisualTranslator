# TEMPLATE = aux

DISTFILES += \
    $$PWD/config/config.xml \
    $$PWD/packages/com.semanser.vt/meta/package.xml \
    $$PWD/packages/com.semanser.visualtranslator/meta/package.xml

win32 {
    # Create installer only on Release build
    CONFIG(release, debug|release) {
        # Path to our installer
        INSTALLER_PATH = $$OUT_PWD/../VisualTranslatorInstaller/VT_install

        # Path to where we copy all necessary files
        DESTDIR_WIN = $$PWD/packages/com.semanser.visualtranslator/data
        DESTDIR_WIN ~= s,/,\\,g

        # Path from where we will copy all the files
        PWD_WIN = $$OUT_PWD/../VisualTranslatorRelease
        PWD_WIN ~= s,/,\\,g

        # Copy all the files to the installer directory
        QMAKE_POST_LINK += $(COPY_DIR) $$PWD_WIN $$DESTDIR_WIN $$escape_expand(\\n\\t)

        # Create a directory for installer
        QMAKE_POST_LINK += $${QMAKE_MKDIR} $$shell_path($$INSTALLER_PATH) $$escape_expand(\\n\\t)
        # Create installer with binarycreator
        QMAKE_POST_LINK += $$(QTDIR)/../../Tools/QtInstallerFramework/3.0/bin/binarycreator --online-only -c $$PWD/config/config.xml -p $$PWD/packages $$INSTALLER_PATH $$escape_expand(\\n\\t)

        # Create a repository
        QMAKE_POST_LINK += $$(QTDIR)/../../Tools/QtInstallerFramework/3.0/bin/repogen -p $$PWD/packages -i com.semanser.visualtranslator --update $$OUT_PWD/../VisualTranslatorRepository
    }
}
