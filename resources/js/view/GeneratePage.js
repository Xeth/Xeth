var GeneratePageView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("updateProgress", "submitEntropy", "skipSeed", "submitForm");
        this.accounts = options.accounts;
        this.template = options.templates.get("generate");
        this.$el.html(this.template());
        this.progress = this.$el.find("#newAddressSeedLoader .loader");
        this.seedPage = this.$el.find("#page_newAddress_seed");
        this.formPage = this.$el.find("#page_newAddress_create");
        this.password = this.$el.find("#newAddressPassword");
        this.stealth = this.$el.find("#newAddress_stealth");
        this.repeatPassword = this.$el.find("#newAddressRepassword");
        this.$el.find("#skipNewAddressSeed").click(this.skipSeed);
        this.$el.find("#createNewAddress").click(this.submitForm);
        this.router = options.router;
    },

    render:function(){
        this.renderSeedPage();
    },

    renderSeedPage:function(){
        this.entropy = "";
        this.updateProgress(0);
        this.formPage.removeClass("active");
        this.seedPage.addClass("active");
        ninja.seeder.init(this.updateProgress, this.submitEntropy);
        $(document).on('mousemove', ninja.seeder.seed);
        $(document).on('click', SecureRandom.seedTime);
        $(document).on('keydown', ninja.seeder.seedKeyPress);
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
        $(document).off('mousemove', ninja.seeder.seed);
        $(document).off('click', SecureRandom.seedTime);
        $(document).off('keydown', ninja.seeder.seedKeyPress);
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
            notifyError("password doesn't match");
            return false;
        }

        var request = {password: password};

        if(this.stealth.is(":checked")){
            request.type = "stealth";
        }

        if(this.entropy){
            request.entropy = this.entropy;
        }

        if(this.accounts.generate(request)){
            var msg = request.type!=undefined ? request.type : "";
            msg += " account generated";
            notifySuccess(msg);
            this.entropy = "";
            this.router.redirect(); //go to default page
        }else{
            notifyError("failed to generate account");
        }
    }

})
