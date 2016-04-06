var GeneratePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "updateProgress", "submitEntropy", "skipSeed", "submitForm");
		SubPageView.prototype.initialize.call(this,options);
        this.accounts = options.accounts;
        this.template = options.templates.get("generate");
        this.router = options.router;
    },
    
    render:function(){
        this.$el.html(this.template());
        this.progress = this.$el.find("#newAddressSeedLoader .loader");
        this.seedPage = this.$el.find("#page_newAddress_seed");
        this.formPage = this.$el.find("#page_newAddress_create");
        this.password = this.$el.find("#newAddressPassword");
        this.stealth = this.$el.find("#newAddress_stealth");
        this.stealth.button({text:false});
        this.repeatPassword = this.$el.find("#newAddressRepassword");
        this.$el.find("#skipNewAddressSeed").click(this.skipSeed);
        this.$el.find("#createNewAddress").click(this.submitForm);
    },
    
    exit:function(){
        this.stopSeedPage();
    },

    open:function(args){
        if(args)
        {
            this.redirectPage = args.redirect ? args.redirect : null;
            this.redirectArgs = (args.redirectArgs && args.redirectArgs instanceof Object) ? args.redirectArgs : {};
            if(args.stealth!=undefined)
            {
                this.stealth.prop("checked",args.stealth).prop("disabled",args.stealth);
                this.stealth.button("refresh");
            }
            else
            {
                this.stealth.prop("disabled",false);
                this.stealth.button("refresh");
            }
        }
        else
        {
            this.redirectPage = this.redirectArgs = null;
            this.stealth.prop("disabled",false);
            this.stealth.button("refresh");
        }
        this.renderSeedPage();
    },

    renderSeedPage:function(){
        this.entropy = "";
        this.password.val("");
        this.repeatPassword.val("");
        this.updateProgress(0);
        this.formPage.removeClass("active");
        this.seedPage.addClass("active");
        ninja.seeder.init(this.updateProgress, this.submitEntropy);
        $(document).on('mousemove', ninja.seeder.seed);
        $(document).on('click', SecureRandom.seedTime);
        $(document).on('keydown', ninja.seeder.seedKeyPress);
    },

    stopSeedPage:function(){
        $(document).off('mousemove', ninja.seeder.seed);
        $(document).off('click', SecureRandom.seedTime);
        $(document).off('keydown', ninja.seeder.seedKeyPress);
    },

    updateProgress:function(percent){
        this.progress.find('.value').css('width', percent+'%');
        this.progress.find('.txt .percent').text(percent);
    },

    skipSeed:function(){
        this.updateProgress(100);
        this.renderForm();
    },

    submitEntropy:function(entropy){
        this.entropy = entropy;
        this.renderForm();
    },

    renderForm:function(){
        this.stopSeedPage();
        this.seedPage.removeClass("active");
        this.formPage.addClass("active");
    },

    submitForm:function(){

        if(!$([this.password, this.repeatPassword]).validate()){
            notifyError("password is mandatory");
            return false;
        }

        var password = this.password.val();
        if(password!=this.repeatPassword.val()){
			this.repeatPassword.error();
            notifyError("password doesn't match");
            return false;
        }

        var request = {password: password};

        if(this.stealth.prop("checked")){
            request.type = "stealth";
        }

        if(this.entropy){
            request.entropy = this.entropy;
        }

        var address = this.accounts.generate(request);
        if(address){
            var msg = request.type!=undefined ? request.type : "";
            msg += " account generated";
            notifySuccess(msg);
            this.entropy = "";
            if(this.redirectPage)
            {
                var request = this.redirectArgs;
                request.address = address;
                this.router.redirect(this.redirectPage, request);
            }
            else
            {
                this.router.redirect("receive", {address:address});
            }
        }else{
            notifyError("failed to generate account");
        }
    }

})
