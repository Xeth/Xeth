<h1>New Address</h1>
<div id="newAddressSeedLoader" class="preloader" loader="0">
    <div class="loader">
        <div class="value" style="width:0%;"></div>
        <span class="txt">generating seed... <span class="percent">0</span>%</span>
    </div>
</div>

<div id="page_newAddress_seed" class="page subpage innerpage">
    <p>randomly move the mouse / click / press keyboard keys to generate the random seed</p>
    
    <div class="formpage">
        <div class="skip">
            <a href="javascript:void(0);" id="skipNewAddressSeed" class="btnSubmit"><span class="txt">Skip</span></a>
    		<p>continue with the system random generator</p>
        </div>
    </div>
</div>
<div id="page_newAddress_create" class="page subpage innerpage">
	<div class="formpage">
        <div class="section_stealth">
            <input id="newAddress_stealth" type="checkbox" class="checkbox" /> Stealth Address (for private exchange of funds)
        </div>
    	<div class="half_left half_equal section_password">
            <h1 error="required">Create Password:</h1>
            <div class="input">
                <input id="newAddressPassword" class="password mandatory" type="password" />
            </div>
        </div>
    	<div class="half_right half_equal section_repassword">
            <h1 error="doesn't match">Repeat Password:</h1>
            <div class="input">
                <input id="newAddressRepassword" class="repassword mandatory" type="password" />
            </div>
        </div>
        <div class="submit">
            <a href="javascript:void(0);" id="createNewAddress" class="btnSubmit"><span class="txt">Create</span></a>
        </div>
    </div>
</div>
