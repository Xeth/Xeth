

<div class="formpage send">
    <h1>From:</h1>
    <div id="sendFrom"></div>
    <div class="group section_to section_mandatory">
        <h1 error="invalid">To:</h1>
        <a class="btn addressbook" title="addressbook" href="javascript:void(0)"></a>
        <a class="btn clipboard" title="paste" href="javascript:javascript:void(0)"></a>
		<select name="sendType" id="sendToType">
			<option value="address">Address</option>
			<option value="bitprofile">BitProfile</option>
		</select>
        <div class="input address">
            <div class="hint" title="copy to clipboard" id="sendToHint"></div>
            <input id="sendToInput" class="mandatory" type="text" placeholder="bitprofile id" />
        </div>
    </div>
    <div class="half_left section_amount section_mandatory">
        <h1 error="required">Amount:</h1>
        <div class="input amount">
            <input id="sendAmount" class="mandatory" type="number" min="0" placeholder="0.00000000000" />
        </div>
    </div>
    <div id="sendFee" class="half_right section_fee" title="fee involves transaction speed">
        <h1>Fee:<span class="fee"><span class="gas"></span><span class="eth"></span></span></h1>
        <div class="slider">
            <div class="handle ui-slider-handle" style="left:20%;"></div>
            <div class="bar"></div>
        </div>
    </div>
    <div class="half_left headless_section section_saveContact">
        <input id="saveContact" type="checkbox" />
		<label for="saveContact">save contact to addressbook</label>
    </div>
    <div class="half_right headless_section section_alias section_mandatory">
        <div class="input">
            <input id="sendAlias" class="mandatory" type="text" placeholder="alias" />
        </div>
    </div>
    <div class="section_submit">
        <div class="half_left section_password section_mandatory">
            <h1 error="incorrect">Password:</h1>
            <div class="input">
                <input id="sendPassword" class="mandatory" type="password" />
            </div>
        </div>
        
        <div class="submit half_right">
            <a href="javascript:void(0);" id="submitSend" class="btnSubmit btnSend"><span class="txt">Send</span></a>
        </div>
    </div>
</div>


