%define        __spec_install_post %{nil}
%define          debug_package %{nil}
%define        __os_install_post %{_dbpath}/brp-compress

Summary: A Ethereum GUI wallet
Name: xeth
Version: 0.3
Release: 2
License: GPLv2
Group: Money
SOURCE0 : %{name}-%{version}.tar.gz
URL: http://xeth.org
Requires: boost-system, boost-filesystem, boost-thread, boost-program-options, boost-random, boost-regex, boost-date-time, boost-chrono, leveldb, jsoncpp, cryptopp, qt5-qtwebkit

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-%{minor}-root
BuildArch: x86_64
%description
%{summary}

%prep
%setup -q

%build
# Empty section.

%install
rm -rf %{buildroot}
mkdir -p  %{buildroot}

# in builddir
cp -a * %{buildroot}


%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
/opt/*
/usr/local/share/applications/*

