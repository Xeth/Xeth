

<div id="bitporfileCreate_details" class="page subpage innerpage">

    <div class="formpage">
        <div class="section_id section_mandatory">
            <h1 error="invalid id">Details:</h1>
            <div class="input bitprofileID">
                <input id="bitprofileCreate_id" type="text" class="mandatory" placeholder="bitprofile ID" />
            </div>
            <select id="bitporfileCreate_context"></select>
        </div>
        <input type="text" class="name" placeholder="Your Name" />
        <input type="text" class="avatarURL" placeholder="image URL" />
        <span class="avatar"><span class="img"><img src="img/avatarEmpty.png" /></span></span>

        <div class="section_mandatory">
            <h1>Link stealth address:</h1>
            <div id="bitprofileCreateStealthList" class="mandatory"></div>
        </div>
        <h1><span class="controls generate off_pending"><a href="javascript:void(0);">Generate new address</a></span></h1>
        
        <div class="submit off_pending">
            <a href="javascript:void(0);" class="btnSubmit"><span class="txt">Next</span></a>
            <a href="javascript:void(0);" class="submitCancel">Reset</a>
        </div>
    
    </div>

</div>

<div id="bitporfileCreate_payment" class="page subpage innerpage">

    <div class="formpage">
        
        <div class="sendFrom section_mandatory">
            <h1>Registration fee:</h1>
            <div id="bitprofileCreateAccountList" class="mandatory"></div>
        </div>
        
        <h1 id="bitprofileCreateAccountBalance">
            Balance:
            <span class="amount txtBalance">
                    <span class="int"></span><span class="dec"></span>
            </span>
        </h1>

        <div class="section_fee" title="fee involves transaction speed">
            <h1><span class="fee"><span class="gas"></span><span class="eth"></span></span></h1>
            <div class="slider">
                <div class="handle ui-slider-handle" style="left:20%;"></div>
                <div class="bar"></div>
            </div>
        </div>

        <div class="submit off_pending">            
            <div class="section_password section_mandatory">
                <h1>Security key:</h1>
                <input id="bitprofileCreate_password" type="password" class="password mandatory" placeholder="Password" />
            </div>

            <a href="javascript:void(0);" class="btnSubmit"><span class="txt">Submit</span></a>
            <a href="javascript:void(0);" class="submitCancel">Back</a>
        </div>
    
    </div>

</div>

<div class="pendingBox on_pending">
    <h1>Processing...</h1>
    <span>Please be patient. This may take a few minutes</span>
</div>

