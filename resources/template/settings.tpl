

<div class="formpage">
	<h1>Address settings:</h1>
    <div class="btns x2">
        <a href="javascript:void(0);" rel="export" class="btn">Backup Key</a>
        <a href="javascript:void(0);" rel="password" class="btn">Change Password</a>
    </div>
    <div class="btns x2">
        <a href="javascript:void(0);" rel="import" class="btn">Import Key</a>
        <a href="javascript:void(0);" rel="generate" class="btn">New Address</a>
    </div>
	<h1>System tray:</h1>
    <div class="section_tray">
        <input id="trayToggle" type="checkbox" />
        <label for="trayToggle">Show system tray icon</label>
        <input id="trayMinimize" type="checkbox" />
        <label for="trayMinimize">minimize to tray</label>
        <input id="trayClose" type="checkbox" />
        <label for="trayClose">close to tray</label>
    </div>
    <div class="section_client btns">
        <a href="javascript:void(0);" rel="update" class="btn">Change Ethereum Client <span class="ver">
        <%
            var version = info.getClientVersion();
            print(version.length > 20 ? (version.substr(0, 20)+"..."):version);
        %></span></a>
    </div>
</div>


