(function ($) {
  var selectedParty;
  var firstCall = true;
  $(document).ready(function() {
    var fractions = $('.views-field-field-fraction');
    var partiesFilter = $('#edit-supported-parties-filter');
    var partyDelegateCheckbox = $('.group-resolution-votes').find('.form-checkbox');
    selectedParty = partiesFilter.val();
    fractions.each(toggleRows);
    partiesFilter.change(filterDelegates);
    partyDelegateCheckbox.each(hideCheckedDelegates);
    partyDelegateCheckbox.click(hideCheckedDelegates);
  });

  function filterDelegates() {
    var fractions = $('.views-field-field-fraction');
    selectedParty = $(this).val();
    fractions.each(toggleRows);
  }

  function toggleRows() {
    var currentFraction = $(this).children('.field-content').text();
    var formItem = $(this).parents('.form-type-checkbox').not('.already-checked');

    if (currentFraction !== selectedParty) {
      formItem.hide();
    } else {
      formItem.show();
    }
  }

  function hideCheckedDelegates() {
    var firstCall = false;
    var anotherTabs = $(this).parents('.field-group-tab').siblings();
    var checkedDelegate = $(this).next().text();
    var anotherTabsCheckboxes = anotherTabs.find('.form-checkbox');
    if ($(this).is(':checked')) {
      anotherTabsCheckboxes.each(function() {
        var checkBoxText = $(this).next().text();
        if (checkBoxText === checkedDelegate) {
          var formItem = $(this).parent();
          formItem.hide();
          formItem.addClass('already-checked');
        }
      });
    } else {
      anotherTabsCheckboxes.each(function() {
        var checkBoxText = $(this).next().text();
        if (checkBoxText === checkedDelegate && firstCall) {
          var formItem = $(this).parent();
          formItem.hide();
          formItem.removeClass('already-checked');
        }
      });
    }
  }

})(jQuery);